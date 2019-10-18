import argparse as ap
import cv2
import numpy as np
import os
from sklearn.externals import joblib
from scipy.cluster.vq import *

from sklearn import preprocessing
import numpy as np

import matplotlib.pyplot as plt
from PIL import Image

# Get the path of the training set
"""
parser = ap.ArgumentParser()
parser.add_argument("-i", "--image", help="Path to query image", required="True")
args = vars(parser.parse_args())
# Get query image path
image_path = args["image"]
"""
data_path = "dataset/logo_dataset/"
imagePathsTest = []
exts = ['jpg', 'png', 'jpeg', 'JPG']
if os.path.isfile(data_path):
    imagePathsTest.append(data_path)
else:
    for parent, dirnames, filenames in os.walk(data_path):
        for filename in filenames:
            for ext in exts:
                if filename.endswith(ext):
                    imagePathsTest.append(os.path.join(parent, filename))
                    break
    print('Find {} images'.format(len(imagePathsTest)))

# Load the classifier, class names, scaler, number of clusters and vocabulary
im_features, image_paths, idf, numWords, voc = joblib.load("bof.pkl")

# Start
sample = 0
ture_sample = 0
for imagePathTest in imagePathsTest:

    # Create feature extraction and keypoint detector objects
    descriptor = cv2.xfeatures2d.SIFT_create()

    # List where all the descriptors are stored
    des_list = []

    im = cv2.imread(imagePathTest)
    kpts, des = descriptor.detectAndCompute(im, None)

    des_list.append((imagePathTest, des))

    # Stack all the descriptors vertically in a numpy array
    descriptors = des_list[0][1]

    #
    test_features = np.zeros((1, numWords), "float32")
    words, distance = vq(descriptors, voc)
    for w in words:
        test_features[0][w] += 1

    # Perform Tf-Idf vectorization and L2 normalization
    test_features = test_features * idf
    test_features = preprocessing.normalize(test_features, norm='l2')

    score = np.dot(test_features, im_features.T)
    rank_ID = np.argsort(-score)

    if image_paths[rank_ID[0][1]].split('-')[-2] == imagePathTest.split('-')[-2]:
        ture_sample += 1
    sample += 1
    if ~sample % 10:
        print("%d graph search done" % sample)

print("accuracy:%f" % (ture_sample / len(imagePathsTest)))

# Visualize the results
plt.figure()
plt.gray()
plt.subplot(5, 4, 1)
plt.imshow(im[:, :, ::-1])
plt.axis('off')
for i, ID in enumerate(rank_ID[0][0:16]):
    print(image_paths[ID], ID)
    img = Image.open(image_paths[ID])
    plt.gray()
    plt.subplot(5, 4, i + 5)
    plt.imshow(img)
    plt.axis('off')

plt.show()