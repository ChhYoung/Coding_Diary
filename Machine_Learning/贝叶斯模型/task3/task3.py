# using sklearn
from sklearn import tree
from sklearn.preprocessing import OneHotEncoder,LabelEncoder
from sklearn.externals.six import StringIO
import pandas as pd
import numpy as np
if __name__ == '__main__':
    train_data = pd.read_csv('./train/train_data.txt',sep='\t',header=None)
    train_label = pd.read_csv('./train/train_labels.txt',sep='\t',header=None)
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

    
    TrainSet = pd.DataFrame(train_data_dict).T.iloc[0:20000,:]
    #TrainSet = pd.DataFrame(train_data_dict).iloc[:,0:20000]
    train_target = train_label.iloc[0:20000,:]
    TestSet = pd.DataFrame(train_data_dict).T.iloc[20000:25000,:]
    #TestSet = pd.DataFrame(train_data_dict).iloc[:,20000:25000]
    target = train_label.iloc[20000:25000,:]
    """
    acc = []
    #for depth in range(100,1000,10):##########TODO
    for depth in range(4,100):##########TODO
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
"""
    #m_index = acc.index(max(acc))
    #clf = tree.DecisionTreeClassifier(max_depth = m_index*10+10)##########TODO
    clf = tree.DecisionTreeClassifier(max_depth = None)##########TODO
    clf = clf.fit(TrainSet,train_target)

    true_test_data = pd.read_csv('./test/test_data.txt',sep='\t',header=None)
    with open('./test/test_data.txt','r') as fr:
        test_data_list = [line.strip().split('\t') for line in fr.readlines()]
    test_data_dict = {}
    for i in range(true_test_data.index.size):
        for item in [int(s) for s in test_data_list[i][0].split() if s.isdigit()]:
            vector[item] = 1
        test_data_dict[i]=[]
        test_data_dict[i].extend(vector)
        vector = [0 for i in range(10000)]
    #true_TestSet = pd.DataFrame(train_data_dict).T
    true_TestSet = pd.DataFrame(train_data_dict)
    pred_target = []
    for i in range(true_test_data.index.size):
        #m = clf.predict([TestSet.iloc[i,:]]).tolist()
        m = clf.predict([true_TestSet.iloc[:,i]]).tolist()
        pred_target.extend(m)
    np.savetxt("test_v2.txt", pred_target,fmt = '%d')
    print('done!')


