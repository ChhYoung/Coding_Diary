import task1
from numpy import *
import sklearn
from sklearn.naive_bayes import BernoulliNB
from sklearn.naive_bayes import GaussianNB
################## binary naive bayes ##########################

#朴素贝叶斯分类器训练函数
#  input: trainMatrix: 文档矩阵
#        trainCategory: 每篇文章类别标签构成的向量
#  output : p(X|c)
#
def trainNB0(trainMatrix,trainCategory):
    # number of training docs
    numTrainDocs = len(trainMatrix)
    # number of vocab in training docs
    numWords = len(trainMatrix[0])

    # p(c = 1)
    pAusive = sum(trainCategory)/float(numTrainDocs)
    # p(X|c) vector
    p0Num = np.ones(numWords) # n X 1
    p1Num = np.ones(numWords)
    #初始化概率
    p0Denom = 2.0
    p1Denom = 2.0
    #对每篇训练文档
    #   对每个类别：
    #       词条出现在文档-->增加该词条的计数
    #       增加所有词条的计数
    #   对每个类别：
    #       对每个词条：
    #           该词条数除以总词条数得到条件概率
    for i in range(numTrainDocs):
        if trainCategory[i] ==1:
            p1Num += trainMatrix[i]       #出现词计数  
            p1Denom += sum(trainMatrix[i]) #计算该类别词总个数
        else:
            p0Num += trainMatrix[i]
            p0Denom += sum(trainMatrix[i])
    #对每个元素做除法
    # p(X|c) vector
    p1Vect = np.log(p1Num / p1Denom)
    p0Vect = np.log(p0Num / p0Denom)
    return p0Vect,p1Vect,pAusive

def classifyNB(vec2Classify,p0Vect,p1Vect,pClass1):
    p1 = sum(vec2Classify * p1Vect) + np.log(pClass1)
    p0 = sum(vec2Classify * p0Vect) + np.log(1.0 - pClass1)
    if p1 > p0:
        return 1
    else :
        return 0

###################### processing the data ####################
#1. get all spam data and ham data
#2. using vali set to split the data set 

def spamTest():
    docList = []; classList = []; fullText = []
    for i in range(1, 26):
        wordList = task1.textParse(open('./spam/%d.txt' % i, encoding="ISO-8859-1").read())
        docList.append(wordList)
        fullText.extend(wordList)
        classList.append(1)
        wordList = task1.textParse(open('./ham/%d.txt' % i, encoding="ISO-8859-1").read())
        docList.append(wordList)
        fullText.extend(wordList)
        classList.append(0)
    vocabList = task1.createVocabList(docList)#create vocabulary
    trainingSet = range(50); testSet = []           #create test set
    for i in range(10):
        randIndex = int(np.random.uniform(0, len(trainingSet)))
        testSet.append(trainingSet[randIndex])
        del(list(trainingSet)[randIndex])
    trainMat = []; trainClasses = []
    for docIndex in trainingSet:#train the classifier (get probs) trainNB0
        trainMat.append(task1.bagOfWords2VecMN(vocabList, docList[docIndex]))
        trainClasses.append(classList[docIndex])
    p0V, p1V, pSpam = trainNB0(np.array(trainMat), np.array(trainClasses))
    errorCount = 0
    for docIndex in testSet:        #classify the remaining items
        wordVector = task1.bagOfWords2VecMN(vocabList, docList[docIndex])
        if classifyNB(np.array(wordVector), p0V, p1V, pSpam) != classList[docIndex]:
            errorCount += 1
            print("classification error", docList[docIndex])
    print('the error rate is: ', float(errorCount)/len(testSet))
    #return vocabList, fullText

if __name__ == '__main__':
    spamText()