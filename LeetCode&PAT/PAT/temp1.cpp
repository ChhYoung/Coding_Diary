// ad 1087 
// diji
#include<iostream>
#include<map>
#include<algorithm>
#include<string>
using namespace std;
int n,k;
const int MAXV = 210;
const int inf = 99999999;
int G[MAXV][MAXV], d[MAXV], weight[MAXV], w[MAXV];
// 节点路径数量， 顶点数量， 前驱
int num[MAXV]={0}, pt[MAXV]={0},pre[MAXV];
bool visit[MAXV] = { false };
map<string, int> cityToIndex;
map<int, string> indexToCity;

void diji(int s){
    fill(d, d+MAXV, inf);
    for(int i=0; i<n; ++i) pre[i] = i;
    d[s] = 0;
    w[s] = weight[0];
    num[s] = 1;
    for(int i=0; i<n; ++i){
        int u=-1, minn=inf;
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
                    d[v] = d[u] + G[u][v];
                    w[v] = w[u] + weight[v];
                    num[v] = num[u];
                    pre[v] = u;
                    pt[v] = pt[u] + 1;
                }
                else if(d[v] == d[u] + G[u][v]){
                    num[v] = num[v] + num[u];
                    if(w[v] < w[u] + weight[v]){
                        w[v] = w[u] + weight[v];
                        pre[v] = u;
                        pt[v] = pt[u] + 1;
                    }
                    else if(w[v] == w[u] + weight[v]){
                        double vAvg = 1.0 * w[v] / pt[v];
                        double uAvg = 1.0 * (w[v] = w[u] + weight[v])/(pt[u] + 1);
                        if(uAvg > vAvg){
                            pre[v] = u;
                            pt[v] = pt[u] + 1;
                        }
                    }
                }
            }
        }
    }
}

// 输出
void printPath(int v){
    if(v == 0){
        cout<<indexToCity[v];
        return;
    }
    printPath(pre[v]);
    cout<<"->"<<indexToCity[v];
}

int main(){
    fill(G[0], G[0]+MAXV*MAXV, inf);
    string start, city1, city2;
    cin>>n>>k>>start;

    cityToIndex[start] = 0;
    indexToCity[0] = start;

    for(int i=1; i<n; ++i){
        cin>>city1>>weight[i];
        cityToIndex[city1] = i;
        indexToCity[i] = city1;
    }

    for(int i=0; i<k; ++i){
        int cost;
        cin>>city1>>city2>>cost;
        int a = cityToIndex[city1];
        int b = cityToIndex[city2];
        G[a][b] = G[b][a] = cost;
    }

    diji(0);
    int rom = cityToIndex["ROM"];
    printf("%d %d %d %d\n",num[rom],d[rom],w[rom],w[rom]/pt[rom]);
    printPath(rom);
    return 1;
}
