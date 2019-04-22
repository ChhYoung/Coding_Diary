import numpy as np
import pandas as pd
import numpy as np
import pandas as pd
import torch
import copy
from torch import nn
from torch.utils.data import DataLoader
from torch.utils.data import TensorDataset
from torch import Tensor

train = pd.read_csv('dataAll.csv')
test = pd.read_csv('testAll.csv')
train_data=train.iloc[:,:30].applymap(lambda x: x+126.23)
train_loc = train.iloc[:,30:]

x_test = test.applymap(lambda x: x+126.23)
x_test = torch.from_numpy(
       x_test.values.astype(np.float32))

train_feat = torch.from_numpy(
        train_data.values.astype(np.float32))
train_labels = torch.from_numpy(
        train_loc.values.astype(np.float32))

num_train = int(0.8 * train_feat.shape[0]) # 划分训练样本和验证集样本
indices = np.arange( train_feat.shape[0])
np.random.shuffle(indices)  # shuffle 顺序
train_indices = indices[:num_train]
valid_indices = indices[num_train:]

train_features = train_feat[train_indices,:]
train_label = train_labels[train_indices,:]
valid_features  = train_feat[valid_indices,:]
valid_labels = train_labels[valid_indices,:]

feat_dim = train_data.shape[0]

def error(y_test,y_pre):
    y_test = np.array(y_test)
    y_pre = np.array(y_pre)
    m = y_test-y_pre
    m=np.square(m)
    m=m.sum(axis=1)
    m=np.sqrt(m)
    return m.sum()/len(y_test)

def get_model(feat_dim,output_dim = 2 ):
    net = nn.Sequential(
        nn.Linear(int(feat_dim), int(feat_dim)),
        nn.BatchNorm1d(int(feat_dim)),
        nn.ReLU(inplace=True),
        
        nn.Linear(int(feat_dim), int(feat_dim)),
        nn.BatchNorm1d(int(feat_dim)),
        nn.ReLU(inplace=True),
        
        nn.Linear(int(feat_dim), int(feat_dim)),
        nn.BatchNorm1d(int(feat_dim)),
        nn.ReLU(inplace=True),
        
        nn.Linear(int(feat_dim), int(feat_dim*4/5)),
        nn.BatchNorm1d(int(feat_dim*4/5)),
        nn.ReLU(inplace=True),
        
        nn.Linear(int(feat_dim*4/5),int(feat_dim*3/5)),
        nn.BatchNorm1d(int(feat_dim*3/5)),
        nn.ReLU(inplace=True),
        
        nn.Linear(int(feat_dim*3/5),int(feat_dim*2/5)),
        nn.BatchNorm1d(int(feat_dim*2/5)),
        nn.ReLU(inplace=True),
        
        nn.Linear(int(feat_dim*2/5),int(feat_dim/5)),
        nn.BatchNorm1d(int(feat_dim/5)),
        nn.ReLU(inplace=True),
        
        nn.Linear(int(feat_dim/5), output_dim)
        )
    return net

def get_data(x,y,batch_size,shuffle):
    dataset = TensorDataset(x,y)
    return DataLoader(dataset, batch_size, shuffle=shuffle,num_workers=4)

def train_model(model,x_train,y_train,x_valid,y_valid,epochs,batch_size,lr,weight_decay,use_gpu):
    
    if use_gpu:
        model = model.cuda()
    train_data = get_data(x_train,y_train,batch_size,True)

    optimizer = torch.optim.Adam(model.parameters(), lr=lr, weight_decay=weight_decay)
    criterion = nn.MSELoss()
    #criterion = nn.CrossEntropyLoss()
    best_error = 0
    for e in  range(epochs):
        model.train()
        for data in train_data:
            x,y = data
            if use_gpu:
                x = x.cuda()
                y = y.cuda()
                
            out = model(x)
            loss = criterion(out, y)
            
            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
        if use_gpu:
                x_valid = x_valid.cuda()
        with torch.no_grad():
            output = model(x_valid)
        output = Tensor.cpu(output)
        out = output.numpy()
        print('epoch:{}'.format(e))
        error_i = error(out,y_valid)
        print('error:{}'.format(error_i)) 
        if e == 0:
            best_error = error_i
        elif error_i < best_error:
            best_model = copy.deepcopy(model)
    torch.save(best_model,"model_NN_master.t7")

def predict(x_test,use_gpu):
    net = torch.load('./model_NN_master.t7')
    if use_gpu:
        x_test = x_test.cuda()
    with torch.no_grad():
        a = Tensor.cpu(net(x_test)).numpy()
    #a = net(x_test).detach().numpy()
    #a = np.argmax(a,axis=1)
    #np.savetxt('NN_ans.txt',np.array(a),fmt='%f')
    #print(a)
    a = pd.DataFrame(a)
    a.to_csv('NN_base.csv',header=None)
    '''
    with open('./NN_master_ans.txt','w') as f:
        for i in a:
            f.write('{}'.format(i))
            f.write('\n')'''
# 可以调整的超参
batch_size = 128
epochs = 40000
lr = 0.001
wd = 0
use_gpu = True
feat_dim = train_feat.shape[1]
net = get_model(feat_dim)
#train_model(net, train_features, train_label, valid_features, valid_labels, epochs, 
           # batch_size, lr, wd, use_gpu)
#predict(x_test,use_gpu)
from graphviz import Digraph
from torchviz import make_dot

y = net(torch.autograd.Variable(x_test))
#print(y)

make_dot(y)
