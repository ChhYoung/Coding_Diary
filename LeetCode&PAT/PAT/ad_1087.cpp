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
// d最短距离， w最大点权和，num[]最短路径条数,
//  pt最短路径的顶点数，pre[]前驱
int d[MAXV]={0}, w[MAXV]={0}, num[MAXV]={0}, pt[MAXV]={0},pre[MAXV];
bool visit[MAXV]={false};
map<string, int> cityToIndex;
map<int, string> indexToCity;

// 起点 s
void diji(int s){
    // 初始化最短距离
    fill(d,d+MAXV,inf);
    for(int i=0; i<n; ++i) pre[i] = i;
    d[s] = 0;
    w[s] = weight[s];
    num[s] = 1;
    for(int i=0; i<n; ++i){
        int u=-1, minn = inf;
        // 找到当前最小的d[]
        for(int j=0; j<n; ++j){
            if(visit[j] == false && d[j] < minn ){
                u = j;
                minn = d[j];
            }
        }
        if(u == -1) return;
        visit[u] = true;
        for(int v=0; v<n; ++v){
            if(visit[v] == false && G[v][u] != inf){
                if(d[v] > d[u]+G[u][v]){
                    d[v] = d[u]+G[u][v];
                    w[v] = w[u]+weight[v];
                    num[v] = num[u];
                    pre[v] = u;
                    pt[v] = pt[u]+1;
                }
                else if(d[v] == d[u]+G[u][v]){
                    num[v] += num[u];
                    if(w[v] < w[u]+weight[v]){
                        w[v] = w[u]+weight[v];
                        pre[v] = u;
                        pt[v] = pt[u]+1;
                    }
                    else if(w[v] == w[u]+weight[v]){
                        double vAvg = 1.0 * w[v] / pt[v];
                        double uAvg = 1.0 * (w[u]+weight[v]) / (pt[u] + 1);
                        if(uAvg > vAvg){
                            pre[v] = u;
                            pt[v] = pt[u]+1;
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
    fill(G[0],G[0]+MAXV*MAXV, inf);
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
        G[cityToIndex[city1]][cityToIndex[city2]] = G[cityToIndex[city2]][cityToIndex[city1]] = cost;
    }

    diji(0);
    int rom = cityToIndex["ROM"];
    printf("%d %d %d %d\n",num[rom],d[rom],w[rom],w[rom]/pt[rom]);
    printPath(rom);
    return 1;
}