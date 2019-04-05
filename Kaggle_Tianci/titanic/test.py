import pandas as pd
import numpy as np
from pandas import DataFrame ,Series

data_train = pd.read_csv("train.csv")

import matplotlib.pyplot as plt
fig = plt.figure()
#图案颜色
fig.set(alpha = 0.2)

# 获救
plt.subplot2grid((2,3),(0,0))
data_train.Survived.value_counts().plot(kind = 'bar')
plt.title('Surivred')
plt.ylabel('amount')

# 乘客等级分布
plt.subplot2grid((2,3),(0,1))
data_train.Pclass.value_counts().plot(kind = 'bar')
plt.title('pclass')
plt.ylabel('amount')

# 年龄
plt.subplot2grid((2,3),(0,2))
plt.scatter(data_train.Survived,data_train.Age)
plt.grid(b=True,which='major',axis='y')
plt.title('age')
plt.ylabel('amount')

# 舱等级
plt.subplot2grid((2,3),(1,0),colspan = 2)
data_train.Age[data_train.Pclass == 1].plot(kind='kde')
data_train.Age[data_train.Pclass == 2].plot(kind='kde')
data_train.Age[data_train.Pclass == 3].plot(kind='kde')
plt.xlabel('age')
plt.ylabel('prob_dense')
plt.title('plcass')
plt.legend(('1','2','3舱'),loc = 'best')

# 登船口
plt.subplot2grid((2,3),(1,2))
data_train.Embarked.value_counts().plot(kind = 'bar')
plt.title('embarked')
plt.ylabel('amount')
plt.show()

# 等级与获救情况的关系
from sklearn.ensemble import RandomForestRegressor

def set_missing_ages(df):
    #把已有的数值型特征提取出来放进RandomForestRegressor中
    age_df = df[['Age','Fare','Parch','Sibsp','Pclass']]

    #乘客分为已知年龄和未知年龄
    known_age = age_df[age_df.Age.notnull()].as_matrix()
    unknown_age = age_df[age_df.Age.isnull()].as_matrix()

    #y即为目标年龄
    y = known_age[:,0]

    #x为特征属性
    X = known_age[:,1:]

    rfr = RandomForestRegressor(random_state=0,n_estimators=2000,n_jobs=-1)
    rfr.fit(X,y)

    predictedAges = rfr.predict(unknown_age[:,1::])

    df.loc[(df.Age.isnull()),'Age'] = predictedAges

    return df,rfr
def set_Cabin_type(df):
    df.loc[(df.Cabin.notnull()),'Cabin']='Yes'
    df.loc[(df.Cabin.isnull()),'Cabin']='No'
    return df

data_train,rfr=set_missing_ages(data_train)
data_train =set_Cabin_type(data_train)


