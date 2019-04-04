#coding: utf-8
import warnings
warnings.filterwarnings("ignore")
import os
import time
import random
import jieba
import sklearn

import numpy as np
from numpy import vstack
from sklearn import metrics
from sklearn.model_selection import PredefinedSplit
from sklearn.model_selection import GridSearchCV
from sklearn.naive_bayes import MultinomialNB
from sklearn.feature_extraction.text import CountVectorizer
from sklearn.feature_extraction.text import TfidfTransformer

import matplotlib.pyplot as plt

#cross validation 
def cos_vali(data_list,class_list,test_size = 0.2):
    data_class_list = list(zip(data_list, class_list))
    random.shuffle(data_class_list)
    index = int(len(data_class_list)*test_size)#+1
    train_list = data_class_list[index:]
    test_list = data_class_list[:index]
    train_data_list, train_class_list = zip(*train_list)
    test_data_list, test_class_list = zip(*test_list)
    return train_data_list, test_data_list, train_class_list, test_class_list

# train and predict 
def TextClassifier(train_feature_list, test_feature_list, 
                    train_class_list, test_class_list,test_list):
    """
    函数说明:分类器
    Parameters:
        train_feature_list - 训练集向量化的特征文本
        test_feature_list - 测试集向量化的特征文本
        train_class_list - 训练集分类标签
        test_class_list - 测试集分类标签
        test_list       - 要预测的
    Returns:
        test_accuracy - 分类器精度
    """
    #train_feature_list = list(train_feature_list)
    train_class_list = list(train_class_list)
    #test_feature_list = list(test_feature_list)
    test_class_list = list(test_class_list)

    X_train = train_feature_list
    Y_train  = train_class_list

    X_train_c = np.copy(train_feature_list)
    Y_train_c  = np.copy(train_class_list)
    
    X_val  = test_feature_list
    Y_val = test_class_list

    len_X_train = len(X_train)
    len_X_val = len(X_val)

    X = vstack([X_train,X_val])
    X = np.array(X)
    Y_train.extend(Y_val)
    Y = np.array(Y_train)

    #Mark the training-validation splits
    train_i = np.ones((len_X_train,), dtype = int) * -1
    valid_i = np.zeros((len_X_val,), dtype = int)
    split_fold = np.concatenate((train_i, valid_i))
    ps = PredefinedSplit(split_fold)
    
    params = {'alpha':np.linspace(0.0001,1,10000)}
    classifier = MultinomialNB()
    
    param_search = GridSearchCV(classifier,
                            params, 
                    scoring=metrics.make_scorer(metrics.f1_score, average='macro'),
                                cv=ps,
                                return_train_score=True)
    param_search.fit(X,Y)
    results = param_search.cv_results_
    best_params = param_search.best_params_ 
    
    clf = MultinomialNB(alpha = best_params['alpha'])
    clf.fit(X_train_c,Y_train_c)
    #validation
    Y_pred = clf.predict(X_val)
    vali_accuracy = metrics.f1_score(Y_val, Y_pred, average='macro')
    
    pred_target = clf.predict(test_list)
    
    return vali_accuracy,pred_target


if __name__ == '__main__':
    #train_data = pd.read_csv('./train/train_data.txt',sep='\t',header=None)
    #train_label = pd.read_csv('./train/train_labels.txt',sep='\t',header=None)
    with open('./train/train_data.txt','r') as fr:
        train_data_list = [line.strip().split('\t') for line in fr.readlines()]
    with open('./train/train_labels.txt','r') as fr:
        train_label_list = [line.strip().split('\t') for line in fr.readlines()]
        # predict
    with open('./test/test_data.txt','r') as fr:
        test_list = [line.strip().split('\t') for line in fr.readlines()]
        
    #get it to right countV format
    train_feature_list = [" ".join(x) for x in train_data_list ]
    train_label_list = [" ".join(x) for x in train_label_list]
    test_list = [" ".join(x) for x in test_list ]
    
    # split the dataset
    train_data_list, test_data_list, train_class_list, test_class_list = cos_vali(train_feature_list,train_label_list,test_size = 0.2)
    
    # extract the feature
    vectorizer = CountVectorizer(max_df=0.85,max_features=1000)

    tfidf_transformer = TfidfTransformer(smooth_idf=True,use_idf=True)
    tfidf = tfidf_transformer.fit_transform(vectorizer.fit_transform(train_data_list))
    tf_idf_vector=tfidf_transformer.transform(vectorizer.transform(test_data_list))

    pred_vect = tfidf_transformer.transform(vectorizer.transform(test_list))
    
    vali_accuracy, pred_target = TextClassifier(tfidf.toarray().tolist(), tf_idf_vector.toarray().tolist(),train_class_list, test_class_list,pred_vect.toarray().tolist())
    
    a = []
    for i in pred_target:
        a.append([ord(i)-48])
    np.savetxt("test_v1.txt", a,fmt = '%d')
    print(vali_accuracy)
    