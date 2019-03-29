from sklearn import tree
import pandas as pd
import numpy as np

TrainSet = pd.read_csv('TrainDT.csv',encoding='gbk')
fin_type = TrainSet.iloc[:,-1].unique()
BSSID_type = TrainSet.iloc[:,0].unique()
Room_type = TrainSet.iloc[:,2].unique()

fin = {}
BSSID_list = np.asarray([0 for i in range(len(BSSID_type))])
#BSSID_list = [0 for i in range(len(BSSID_type))]
for fin_i in fin_type:
    indexx = []
    TD_index = pd.Index(TrainSet.iloc[:,-1])
    sliced_TD = TrainSet[TD_index.get_loc(fin_i)]
    for i in sliced_TD.iloc[:,0]:
        index = pd.Index(BSSID_type).get_loc(i)
        #indexx.extend([index])
        indexx.append(index)
    BSSID_list[np.asarray(indexx)] = 1 
    fin[fin_i] = []
    fin[fin_i].extend(BSSID_list.tolist())
    # add label at the end
    fin[fin_i].extend([sliced_TD.iloc[0,2]]) 
    
Label_name = []
BSSID_name = BSSID_type.tolist()
Label_name.extend(BSSID_name)
BSSID_name.extend(['target'])

pdf_fin = pd.DataFrame(fin).T
pdf_fin.columns =  BSSID_name
feature_data = pdf_fin.iloc[:,0:len(BSSID_type)]
target = pdf_fin.iloc[:,len(BSSID_type)]

TestSet = pd.read_csv('TestDT.csv',encoding='gbk')
t_fin_type = TestSet.iloc[:,-1].unique()
t_BSSID_type = TestSet.iloc[:,0].unique()
t_Room_type = TestSet.iloc[:,2].unique()

t_fin = {}
t_BSSID_list = np.asarray([0 for i in range(len(BSSID_type))])
#BSSID_list = [0 for i in range(len(BSSID_type))]
for fin_i in t_fin_type:
    indexx = []
    TD_index = pd.Index(TestSet.iloc[:,-1])
    sliced_TD = TestSet[TD_index.get_loc(fin_i)]
    for i in sliced_TD.iloc[:,0]:
        if i in BSSID_type:
            index = pd.Index(BSSID_type).get_loc(i)
            #indexx.extend([index])
            indexx.append(index)
    t_BSSID_list[np.asarray(indexx)] = 1 
    t_fin[fin_i] = []
    t_fin[fin_i].extend(t_BSSID_list.tolist())
    # add label at the end
    t_fin[fin_i].extend([sliced_TD.iloc[0,2]]) 
    
t_Label_name = []
t_BSSID_name = BSSID_type.tolist()
t_Label_name.extend(BSSID_name)
t_BSSID_name.extend(['target'])

t_pdf_fin = pd.DataFrame(t_fin).T
t_pdf_fin.columns =  t_BSSID_name
t_feature_data = t_pdf_fin.iloc[:,0:len(BSSID_type)]
t_target = t_pdf_fin.iloc[:,len(BSSID_type)]
accuracy = 0
for i in range(100):
    clf = tree.DecisionTreeClassifier(max_depth = None)
    clf = clf.fit(feature_data,target)
    pred_target = []
    for i in range(t_feature_data.index.size):
        m = clf.predict([t_feature_data.iloc[i,:]]).tolist()
        pred_target.extend(m)
    summ = 0
    target_list = t_target.tolist()
    for i in range(t_feature_data.index.size):
        if pred_target[i] == target_list[i]:
            summ += 1
    accuracy += summ / t_feature_data.index.size

print("accuracy:{}".format(accuracy/100))
    
