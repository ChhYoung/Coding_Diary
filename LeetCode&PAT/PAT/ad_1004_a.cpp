#include<iostream>
#include<queue>
#include<vector>

using namespace std;
const int N = 105;

// 树
vector<int> G[N];
//各个节点所处的层号，从1开始 
int h[N] = {0};
// 存放每层的叶子节点个数
int leaf[N] = {0};
int max_h = 0;

void BFS(){
    queue<int> Q;
    // 根节点压入栈
    Q.push(1);
    while(!Q.empty()){
        // 弹出队首指针
        int id = Q.front();
        Q.pop();
        max_h = max(max_h, h[id]);
        if(G[id].size() == 0){
            leaf[h[id]]++;
        }
        for(int i=0; i<G[id].size(); ++i){
            h[G[id][i]] = h[id]+1;
            Q.push(G[id][i]);
        }
    }
}

int main(){
    int n, m;
    cin>>n>>m;
    for(int i=0; i<m; ++i){
        int parent, k, child;
        cin>>parent>>k;
    }

}