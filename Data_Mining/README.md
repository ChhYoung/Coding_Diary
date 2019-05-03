# <center>数据挖掘作业

  <br/><br/><br/><br/>

  <br/><br/><br/><br/>
  <br/><br/><br/><br/>
### <center> 姓名：杨崇焕
### <center> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;学号：U201610531
### <center> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;班级：电信中英1601



  <br/><br/><br/><br/>
    <br/><br/><br/><br/>
      <br/><br/><br/><br/>
        <br/><br/><br/><br/>
<div STYLE="page-break-after: always;"></div>

### 作业一：为什么要对数据进行预处理？数据预处理有哪些基本方法？它们的作用分别是什么？

> - 现实中的数据一般是不完整的，有噪声的和不一致的，数据预处理有助于提高挖掘的质量

> - 基本方法及作用
> - 数据清洗：填写空缺值，平滑噪声，识别删除孤立点，解决不一致性
> - 数据集成：集成多个数据库，数据立方体或文件；合并成一致的数据存储
> - 数据变换：规范化：同一尺度，提高准确性和有效性
> - 数据规约：减少数据规模但得到相同或相近的结果
> - 数据离散化：通过概念分层或数据离散化来规约数据

### 作业二：什么是关联分析？理解Apriori算法并使用你熟悉的程序语言设计Apriori算法

> - 关联分析用于发现隐藏在大型数据集中令人感兴趣的频繁出现的模式，关联和相关性

> -  以下为用python实现的Apriori算法

**Apriori**
```python
from numpy import *
# 生成一个数据集
def loadDatatSet():
    #return [[1, 3, 4], [2, 3, 5], [1, 2, 3, 5], [2, 5]]
    return [[1,2,3],[4,5,6]]
# 生成C1项集
def creatC1(dataSet):
    C1 = []
    for item_1 in dataSet:
        for item_2 in item_1:
            if [item_2] not in C1:
                C1.append([item_2])
    C1.sort()
    return list(map(frozenset, C1))

# 剪枝,生成Lk
# D:数据集 
# Ck：候选项集列表
# minSupport ： 最小支持度
def scanD(D, Ck, minSupport):
    ssCnt = {}
    # 用dict记录候选集中项在数据集出现次数
    for tid in D:
        for can in Ck:
            if can.issubset(tid):
                if can not in ssCnt:
                    ssCnt[can] = 1
                else: ssCnt[can] += 1
    numItems = float(len(D))
    retList = []
    supportData = {}

    # 计算支持度，将频繁项插入到retList中
    # supportData储存Ck中每项的支持度
    for key in ssCnt:
        support = ssCnt[key]/numItems
        if support >= minSupport:
            retList.insert(0,key)
        supportData[key] = support
    return retList, supportData
```
运行结果
![](Ap1.jpg)
```python
# 生成Ck
# 生成时比较每个项的前k-2个元素是否相同（当前项长k-1），
# 如果相同，则通过集合并来生成k长项集
def apriorGen(Lk,k):
    retList = []
    lenLk = len(Lk)
    for i in range(lenLk):
        for j in range(lenLk):
            L1 = list(Lk[i])[:k-2]
            L2 = list(Lk[j])[:k-2]
            L1.sort()
            L2.sort()
            if L1 == L2:
                retList.append(Lk[i] | Lk[j])
    return retList

def apriori(dataSet, minSupport = 0.5):
    C1 = createC1(dataSet)
    D = list(map(set, dataSet))
    L1, supportData = scanD(D, C1, minSupport)
    L = [L1]
    k = 2
    while (len(L[k-2]) > 0):
        Ck = aprioriGen(L[k-2], k)
        Lk, supK = scanD(D, Ck, minSupport)#scan DB to get Lk
        supportData.update(supK)
        L.append(Lk)
        k += 1
    return L, supportData
```
结果
![](ap_JIEGUO.jpg)

### 作业三：简述决策树分类的主要步骤。试比较贝叶斯分类算法和k近邻分类算法。理解ID3算法并用你熟悉的程序设计语言实现ID3算法。

> - 