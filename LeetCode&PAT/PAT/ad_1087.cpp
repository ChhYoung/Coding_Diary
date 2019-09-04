#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

const int  MAXV = 210;
const int inf = 999999999;
int n,k;
int G[MAXV][MAXV], weight[MAXV];
// d最短距离， w最大点权，num[] 最短路径条数, pt最短路径的顶点数，pre[]前驱
int d[MAXV]={0}, w[MAXV]={0}, num[MAXV]={0}, pt[MAXV]={0},pre[MAXV];
bool visit[MAXV]={false};
map<string, int> cityToIndex;
map<int, string> indexToCity;

// 起点 st
void diji(int s){
    fill(G[0],G[0]+MAXV*MAXV, inf);
    for(int i=0; i<n; ++i) pre[i] = i;
    d[s] = 0; w[s] = weight[s] = 0;
    num[s] = 1;
    for(int i=0; i<n; ++i){
        int u=-1, minn = inf;
        for(int j=0; j<n; ++j){
            if(visit[j] == false && d[j] < minn){
                u = j;
                minn = d[j];
            }
        }
        if(u == -1) return;
        visit[u] = true;
        for(int v=0; v<n; ++v){
            if(visit[v] == false && G[u][v] != inf){
                if(d[v] > d[u]+G[u][v]){
                    d[v] = d[u]+G[u][v];
                    w[v] = w[u]+weight[v];
                    num[v] = num[u];
                    pt[v] = pt[u]+1; 
                    pre[v] = u;
                }
                else if(d[v] == d[u]+G[u][v]){
                    num[v] = num[u]+num[v];
                    if(weight[v]+w[u] > w[v]){
                        w[v] = weight[v]+w[u];
                        pt[v] = pt[u]+1;
                        pre[v] = u;
                    }
                    else if(w[v] == weight[v]+w[u]){
                        double uAvg = 1.0*(w[u]+weight[v])/(pt[u]+1);
                        double vAvg = 1.0*w[v]/pt[v];
                        if(uAvg > vAvg){
                            w[v] = weight[v]+w[u];
                            pt[v] = pt[u]+1;
                            pre[v] = u;
                        }
                    }
                }
            }
        }



    }
}