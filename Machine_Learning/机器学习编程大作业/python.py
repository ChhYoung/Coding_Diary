
import numpy as np
import matplotlib.pyplot as plt
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split
from sklearn.multioutput import MultiOutputRegressor


# Create a random dataset

X_train, X_test, y_train, y_test = cos_vali(np.array(data_train_add).tolist(),train_loc_list)
X_train, X_test, y_train, y_test = np.array(X_train),np.array(X_test),np.array(y_train),np.array(y_test)

from sklearn.model_selection import GridSearchCV

param={'max_depth':np.linspace(1,60,60)}
classifier = 
param_search = GridSearchCV(classifier,
                            params, 
                    scoring=metrics.make_scorer(metrics.f1_score, average='macro'),
                                cv=ps,
                                return_train_score=True)










max_depth = 30
regr_multirf = MultiOutputRegressor(RandomForestRegressor(n_estimators=100,
                                                          max_depth=max_depth,
                                                          random_state=0))
regr_multirf.fit(X_train, y_train)

regr_rf = RandomForestRegressor(n_estimators=100, max_depth=max_depth,
                                random_state=2)
regr_rf.fit(X_train, y_train)

# Predict on new data
y_multirf = regr_multirf.predict(X_test)
y_rf = regr_rf.predict(X_test)

# Plot the results
plt.figure()
s = 50
a = 0.4
plt.scatter(y_test[:, 0], y_test[:, 1], edgecolor='k',
            c="navy", s=s, marker="s", alpha=a, label="Data")
plt.scatter(y_multirf[:, 0], y_multirf[:, 1], edgecolor='k',
            c="cornflowerblue", s=s, alpha=a,
            label="Multi RF score=%.2f" % regr_multirf.score(X_test, y_test))
plt.scatter(y_rf[:, 0], y_rf[:, 1], edgecolor='k',
            c="c", s=s, marker="^", alpha=a,
            label="RF score=%.2f" % regr_rf.score(X_test, y_test))
plt.xlim([-6, 6])
plt.ylim([-6, 6])
plt.xlabel("target 1")
plt.ylabel("target 2")
plt.title("Comparing random forests and the multi-output meta estimator")
plt.legend()
plt.show()





import pandas as pd
import numpy as np
from pandas import Series,DataFrame
data_train = pd.read_csv('dataAll.csv')
data_train.head()
data_train_add = data_train.iloc[:,:30].applymap(lambda x: x)
train_loc = data_train.iloc[:,30:]
data_train_add.to_csv("./processed_data/train_pro.csv",index = False)
m = data_train_add.describe()
m.to_csv("./processed_data/des_pro.csv",index = False)

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
X_train, X_test, y_train, y_test = cos_vali(np.array(data_train_add).tolist(),train_loc_list)
train_data_list, test_data_list, train_class_list, test_class_list = cos_vali(np.array(data_train_add).tolist(),train_loc_list)