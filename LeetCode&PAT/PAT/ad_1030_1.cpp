#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int n, m, s, d;
const int inf = 999999;
const int maxn = 510;

int e[maxn][maxn], dis[maxn] , weight[maxn][maxn], w[maxn];
int pre[maxn];
bool visit[maxn];

void diji(int s){
    w[s] = 0;
    dis[s] = 0;
    for(int i=0; i<n; ++i){
        int u=-1, minn=inf;
        for(int j=0; j<n; ++j){
            if(visit[j] == false && dis[j]<minn){
                u = j;
                minn = dis[j];
            }
        }
        if(u == -1) return;
        visit[u] = true;
        for(int v=0; v<n; ++v){
            if(visit[v] == false && e[u][v] != inf){
                if(dis[v] > dis[u]+e[u][v]){
                    dis[v] = dis[u]+e[u][v];
                    w[v] = w[u] + weight[u][v];
                    pre[v] = u;
                }
                else if(dis[v] == dis[u]+e[u][v]){
                    if(w[v] > w[u] + weight[u][v]){
                        w[v] = w[u] + weight[u][v];
                        pre[v] = u;
                    }
                }
            }
        }
    }
}

int main(){
    cin>>n>>m>>s>>d;
    if(s == d) {
        cout<<s<<' '<<d<<' '<<0;
        return 0;
    }

    fill(e[0],e[0]+maxn*maxn, inf);
    fill(dis, dis+maxn, inf);

    for(int i=0; i<m; ++i){
        int a,b,c,d1;
        cin>>a>>b>>c>>d1;
        e[a][b] = e[b][a] = c;
        weight[a][b] = weight[b][a] = d1;
    }
    diji(s);
    vector<int> res;
    int i = d;
    while(i != s){
        res.push_back(i);
        i = pre[i];
    }
    res.push_back(s);
    for(int i=res.size()-1; i>=0; --i){
        cout<<res[i]<<' ';
    }
    cout<<dis[d]<<' '<<w[d];
    return 0;
}
