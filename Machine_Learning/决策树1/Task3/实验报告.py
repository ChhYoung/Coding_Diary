from sklearn import tree
import pandas as pd
import numpy as np


if __name__ == '__main__':

    # get train data and train label
    train_data = pd.read_csv('./train/train_data.txt',sep='\t',header=None)
    train_label = pd.read_csv('./train/train_labels.txt',sep='\t',header=None)
    
    # using one-hot encode to process the data
    with open('./train/train_data.txt','r') as fr:
        train_data_list = [line.strip().split('\t') for line in fr.readlines()]

    vector = [0 for i in range(10000)]
    train_data_dict = {}
    for i in range(train_data.index.size):
        for item in [int(s) for s in train_data_list[i][0].split() if s.isdigit()]:
            vector[item] = 1
        train_data_dict[i]=[]
        train_data_dict[i].extend(vector)
        vector = [0 for i in range(10000)]

    # split the data set to training set and testing set
    TrainSet = pd.DataFrame(train_data_dict).T.iloc[0:20000,:]
    train_target = train_label.iloc[0:20000,:]
    TestSet = pd.DataFrame(train_data_dict).T.iloc[20000:25000,:]
    target = train_label.iloc[20000:25000,:]

    # calculate the accuracy on testing set to get the best depth of the tree
    acc = []
    for depth in range(4,100):
        clf = tree.DecisionTreeClassifier(max_depth= depth)
        clf = clf.fit(TrainSet,train_target)
        pred_target = []
        for i in range(5000):
            m = clf.predict([TestSet.iloc[i,:]]).tolist()
            pred_target.extend(m)
        summ = 0
        target_list = target.iloc[:,0].tolist()
        for i in range(5000):
            if pred_target[i] == target_list[i]:
                summ += 1
        accuracy = summ / 5000
        print("depth = {}\n".format(depth))
        print("accuracy = {}\n".format(accuracy))
        acc.extend([accuracy])  
    # training 
    clf = tree.DecisionTreeClassifier(max_depth = 22)
    clf = clf.fit(TrainSet,train_target)

    # process the test set
    true_test_data = pd.read_csv('./test/test_data.txt',sep='\t',header=None)
    with open('./test/test_data.txt','r') as fr:
        test_data_list = [line.strip().split('\t') for line in fr.readlines()]
    test_data_dict = {}

    # using one-hot encode ,same as the above
    for i in range(true_test_data.index.size):
        for item in [int(s) for s in test_data_list[i][0].split() if s.isdigit()]:
            vector[item] = 1
        test_data_dict[i]=[]
        test_data_dict[i].extend(vector)
        vector = [0 for i in range(10000)]
    true_TestSet = pd.DataFrame(train_data_dict)
    pred_target = []

    # predict and save output to the test.txt
    for i in range(true_test_data.index.size):
        m = clf.predict([true_TestSet.iloc[:,i]]).tolist()
        pred_target.extend(m)
    np.savetxt("test.txt", pred_target,fmt = '%d')
    print('done!')


