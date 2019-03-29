def loadDataSet():
    return [[1,3,4],[2,3,5],[1,2,3,5],[2,5]]

#对C1中每个向构建一个不变的集合
# C1即为大小1的候选集集合
# exp： dataSet = [[1,3,4],[2,3,5],[1,2,3,5],[2,5]]
#       C1 = [[1],[2],[3],[4],[5]]
def createC1(dataSet):
    C1 = []
    for transaction in dataSet:
        for item in transaction:
            if not [item] in C1:
                C1.append([item])
    C1.sort()
    return map(frozenset,C1)


#在D中扫描Ck候选集，选出 support >= p 的项
def scanD(D,Ck,minSpport):
    ssCnt = {}
    for tid in D:
        for can in Ck:
            if can.issubset(tid):
                if not ssCnt.has_key(can):ssCnt[can] = 1
                else: ssCnt[can] += 1
    numItems = float(len(D))
    reList = []
    supportData = {}
    for key in ssCnt:
        support = ssCnt[key] / numItems
        if support >= minSpport:
            reList.insert(0,key)
        supportData[key] = support
    return reList,supportData
