import pandas as pd
import numpy as np
from pandas import Series,DataFrame
import numpy as np
import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.multioutput import MultiOutputRegressor
# data file name  /dataAll.csv  /testAll.csv
data_train = pd.read_csv('dataAll.csv')
#data_train.head()
data_train_add = data_train.iloc[:,:30].applymap(lambda x: x)#+126.23
train_loc = data_train.iloc[:,30:]
data_train_add.to_csv("./processed_data/train_pro.csv",index = False)
m = data_train_add.describe()
m.to_csv("./processed_data/des_pro.csv",index = False)
train_loc_list=[]
for i in range(len(train_loc)):
    train_loc_list.append([train_loc.iloc[i,0],train_loc.iloc[i,1]])
len(train_loc_list)



def cos_vali(data_list,class_list,test_size = 0.2):
    data_class_list = list(zip(data_list, class_list))
    import random
    random.shuffle(data_class_list)
    index = int(len(data_class_list)*test_size)#+1
    train_list = data_class_list[index:]
    test_list = data_class_list[:index]
    train_data_list, train_class_list = zip(*train_list)
    test_data_list, test_class_list = zip(*test_list)
    return list(train_data_list),list(test_data_list),list(train_class_list),list(test_class_list)
# Create a random dataset
def error(y_test,y_pre):
    m = y_test-y_pre
    m=np.square(m)
    m=m.sum(axis=1)
    m=np.sqrt(m)
    return m.sum()/len(y_test)

X_train, X_test, y_train, y_test = cos_vali(np.array(data_train_add).tolist(),train_loc_list)
X_train, X_test, y_train, y_test = np.array(X_train),np.array(X_test),np.array(y_train),np.array(y_test)
regr_multirf = MultiOutputRegressor(RandomForestRegressor(n_estimators=100,
                            max_depth=27,min_samples_leaf=2,oob_score=True))
regr_multirf.fit(X_train, y_train)

y_multirf = regr_multirf.predict(X_test)
       
m=error(y_test,y_multirf)
        
print(m)