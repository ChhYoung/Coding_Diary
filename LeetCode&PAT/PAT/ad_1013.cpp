#include<vector>
#include<iostream>
#include<cstring>
using namespace std;
const int N = 1010;
// 邻接表
vector<int> G[N];
// 看结点是否访问过
bool vis[N];
// 当前要删除结点的编号
int currentPoint;

// 深度优先遍历,从结点v开始
void dfs(int v){
    // 若到达当前删除节点则返回
    if(v == currentPoint) return;
    // 访问
    vis[v] = true;
    // 遍历临界节点
    for(int i=0; i<G[v].size(); ++i){
        if(vis[G[v][i]] == false){
            dfs(G[v][i]);
        }
    }
}

int n,m,k;

int main(){
    cin>>n>>m>>k;
    for(int i=0; i<m; ++i){
        // 两个顶点
        int a,b;
        cin>>a>>b;
        // 边 a->b, b->a
        G[a].push_back(b);
        G[b].push_back(a);
    }
    
    for(int query=0; query<k; query++){
        cin>>currentPoint;
        // 初始化 vis数组为false
        fill(vis,vis+N,false);
        int cnt=0;
        for(int i=1; i<=n; ++i){
            // 未被删除或访问, 在一个单独的连通域
            if(i != currentPoint && vis[i] == false){
                dfs(i);
                cnt++;
            }
        }
        cout<<cnt-1<<endl;
    }
    return 0;
    
}