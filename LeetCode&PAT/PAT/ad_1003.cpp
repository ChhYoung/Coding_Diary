#include<iostream>
#include<algorithm>
using namespace std;
int n,m,c1,c2;
// weight 最大点权和，num最短路径条数
int e[510][510], weight[510], dis[510], num[510],w[510];
bool visit[510];
const int inf = 9999999;
int main(){
    cin>>n>>m>>c1>>c2;
    for(int i=0; i<n; ++i){
        cin>>weight[i];
    }
    fill(e[0],e[0]+510*510,inf);
    fill(dis,dis+510,inf);
    int a,b,c;
    for(int i=0; i<m; ++i){
        cin>>a>>b>>c;
        e[a][b] = e[b][a] = c;
    }
    dis[c1] = 0;
    w[c1] = weight[c1];
    num[c1] = 1;
    for(int i=0;i<n;++i){
        int u=-1, minn = inf;
        // 找到未访问的顶点中，d[]最小的
        for(int j=0;j<n;++j){
            if(visit[j] == false && dis[j] < minn){
                u = j;
                minn = dis[j];
            }
        }
        // 找不到则说明，剩下的顶点不联通
        if(u == -1) break;
        visit[u] = true;
        for(int v=0; v<n; ++v){
            if(visit[v] == false && e[u][v] != inf){
                if(dis[u]+e[u][v] < dis[v]){
                    dis[v] = dis[u]+e[u][v];
                    // 继承最短路径条数
                    num[v] = num[u];
                    w[v] = w[u]+weight[v];
                }
                else if(dis[u] + e[u][v] == dis[v]){
                    if(w[u]+weight[v] > w[v])
                        w[v] = w[u]+weight[v];
                    // 
                    num[v] = num[v] + num[u];
                }
            }
        }
    }
    printf("%d %d",num[c2],w[c2]);
    return 0;
}