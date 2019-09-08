#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int inf = 9999999;
const int maxn = 510;
int n, m, c1 , c2;
int e[maxn][maxn],d[maxn], weight[maxn],w[maxn],num[maxn];
bool visit[maxn];
void diji(int s){
    fill(d, d+maxn, inf);
    d[s] = 0;
    num[s] = 1;
    w[s] = weight[s];
    for(int i=0;i<n;++i){
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
            if(visit[v] == false && e[u][v] != inf){
                if(d[v] > d[u] + e[u][v]){
                    d[v] = d[u] + e[u][v];
                    num[v] = num[u];
                    w[v] = w[u] + weight[v];
                }
                else if(d[v] == d[u] + e[u][v]){
                    num[v] += num[u];
                    if(w[v] < w[u] + weight[v]){
                        w[v] = w[u] + weight[v];
                    }
                }
            }
        }
    }
}

int main(){
    cin>>n>>m>>c1>>c2;
    for(int i=0; i<n; ++i){
        cin>>weight[i];
    }
    fill(e[0],e[0]+maxn*maxn, inf);
    for(int i=0; i<m; ++i){
        int a,b,c;
        cin>>a>>b>>c;
        e[a][b] = e[b][a] = c;
    }
    diji(c1);
    cout<<num[c2]<<' '<<w[c2];
    return 0;
}
