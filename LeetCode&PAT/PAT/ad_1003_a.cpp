#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

/*
weight 每点的权重和
*/
int e[510][510], weight[510], dis[510], num[510], w[510];
bool visit[510];
const int inf =  99999999;

int main(){
    fill(e[0],e[0]+510*510,inf);
    fill(dis,dis+510,inf);
    int N,M,C1,C2;
    cin>>N>>M>>C1>>C2;
    for(int i=0; i<N; ++i){
        cin>>weight[i];
    }
    // 构建邻接矩阵
    for(int i=0; i<M; ++i){
        int c1,c2,L;
        cin>>c1>>c2>>L;
        e[c1][c2] = e[c2][c1] =L;
    }
    // 初始化点到起点的距离
    dis[C1] = 0;
    // 点的权值和，救援队数量
    w[C1] = weight[C1];
    // 最短路径的数量
    num[C1] = 1;
    for(int i=0; i<N; ++i){
        int u = -1, minn = inf;
        // 在未访问的节点中找到u使得 d[u]最小，最小值赋给minn
        for(int j=0; j<N; ++j){
            if(visit[j] == false && dis[j] < minn){
                minn = dis[j];
                u = j;
            }
        }
        // 找不到，即剩下的节点与顶点不连通
        if(u == -1) break;
        visit[u] = true;
        for(int v=0; v<N; ++v){
            if(visit[v] == false && e[u][v] != inf){
                // 以u为中介点能够使起点到v的距离更小
                if(dis[u]+e[u][v] < dis[v]){
                    dis[v] = dis[u]+e[u][v];
                    num[v] = num[u];
                    w[v] = w[u] + weight[v];
                    printf("num[u] is %d, num[v] is %d\n",num[u],num[v]);
                }
                // 当距离相等时，只记录最大的点权值,并记录路径条数
                else if(dis[u]+e[u][v] == dis[v]){
                    if(w[u]+weight[v] > w[v])
                        w[v] = w[u]+weight[v];
                    // 当前u的路径加上之前u的路径即num[v]，则为当前v的路径
                    num[v] = num[v] + num[u];
                    printf("num[u] is %d, num[v] is %d\n",num[u],num[v]);
                }
            }
        }
    }
    printf("%d %d",num[C2],w[C2]);
    return 0;
}
