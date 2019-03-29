import pandas as pd
from math import log
import numpy as np
#从文本个读取数据
#data=pd.read_csv("lenses.txt",sep='\t')


#process the data
data=pd.read_csv("lenses.txt",sep='\t',header=None)
# insert ID at the first column
data.loc[:,0] = range(len(data.index))



########################################
# 统计列不同元素出现的次数
def value_count(column):
    dict = {}
    for i in column:
        if i in dict:
            dict[i] += 1
        else:
            dict[i] = 1
    return np.asarray(list(dict.values()))

##########################
# ##统计列不同元素出现的次数,返回 dict{类型：次数}
def key_value_count(column):
    dict = {}
    for i in column:
        if i in dict:
            dict[i] += 1
        else:
            dict[i] = 1
    return dict


############################################
#  找到某一列对应的target
def column_to_target(index,data):
    target = []
    #for i in index:
       # target.append(data.iloc[i,-1])
    target.append(data.iloc[index,-1])   
    return target


############################################### 
# 计算香农熵
def cal_entropy(counted_value):
    prob = counted_value/sum(counted_value)
    entropy = 0
    for i in prob:
        if i == 0:
            entropy += 0
        else:
            entropy -= i*log(i,2)
    return entropy

############################################ 
# 计算当前分组的信息熵
# input : column_id :   列号，
#             index :   分组的元素的行号  
#             data  ：  processed data
def cal_group_ent(column_id,index,data):
    target = column_to_target(index,data)
    type = data.iloc[index,column_id]

    # get {type : number}
    type_value = key_value_count(type)

    # count {type : prob}
    suml = sum(list(type_value.values()))
    for key in type_value.keys():
        type_value[key] /= suml  


    dict_type={}
    for key in type_value.keys():
        listfe =[]
        for ind in index:
            if(data.iloc[ind,column_id] == key):
                listfe.append(ind)
                dict_type[key] = listfe

    res = 0
    for key,indexx in dict_type.items():
        count_value = value_count(data.iloc[indexx,-1])
        res +=  type_value[key]*cal_entropy(count_value)
    return res




########################################### 
# 计算信息增益
def cal_info_Gain(column_id, index, data):
    Ent_D = cal_group_ent(-1,index,data)
    Group_Ent = cal_group_ent(column_id,index,data)
    return Ent_D - Group_Ent
    
###########################
# 得到当前每种元素的index
def get_type_index(column_id,index,data):
    type = data.iloc[:,column_id]
    type_value = key_value_count(type)

    dict_type={}
    for key in type_value.keys():
        listfe =[]
        for ind in index:
            if(data.iloc[ind,column_id] == key):
                listfe.append(ind)
                dict_type[key] = listfe
    return dict_type

                                                                                             


    


