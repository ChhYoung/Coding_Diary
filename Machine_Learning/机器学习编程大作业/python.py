import pandas as pd
import numpy as np
from pandas import Series,DataFrame
# data file name  /dataAll.csv  /testAll.csv
data_train = pd.read_csv('dataAll.csv')
data_train_add = data_train.iloc[:,:30].applymap(lambda x: x+126.23)
train_loc = data_train.iloc[:,30:]
import matplotlib.pyplot as plt
fig = plt.figure()
fig.set(alpha=0.2)

plt.subplot2grid((2,3),(0,0))
data_train_add.iloc[:,0].value_counts().plot(kind='bar')
plt.title('21000')
plt.ylabel('amount')

plt.show()