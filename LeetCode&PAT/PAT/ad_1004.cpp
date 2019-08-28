#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int N = 100;

// 存放树
vector<int> G[N];
// 存放每层叶节点数
int leaf[N] = {0};
// 树的最高高度
int max_h = 1;
// 方法一 ： DFS
void dfs(int index, int h){
    max_h = max(max_h,h);
    // 若是叶子节点
    if(G[index].size() == 0){
        leaf[h] ++;
        return ;
    }
    for(int i=0; i<G[index].size(); ++i){
        dfs(G[index][i],h+1);
    }
}

int main(){
    int n,m;
    int id,child,k;
    cin>>n>>m;
    for(int i=0; i<m; ++i){
        cin>>id>>k;
        for(int j=0; j<k; j++){
            cin>>child;
            G[id].push_back(child);
        }
    }

    dfs(1,1);
    printf("%d",leaf[1]);
    for(int i=2;i<=max_h;++i)
        printf(" %d",leaf[i]);
    return 0;
}



