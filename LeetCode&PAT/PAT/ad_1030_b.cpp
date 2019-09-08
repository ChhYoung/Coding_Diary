#include<vector>
#include<iostream>
#include<algorithm>

using namespace std;
const int inf = 99999999;

int n, m, s, d;
int e[510][510], dis[510], cost[510][510];
vector<int> tempPath, path;
vector<int> pre[510];
bool visit[510];
int min_cost = inf;

void dfs(int u){
    tempPath.push_back(u);
    if(u == s){
        int tempCost = 0;
        for(int i=tempPath.size()-1; i > 0; --i){
            int id = tempPath[i], id_next = tempPath[i-1];
            tempCost += cost[id][id_next];
        }
        if(tempCost < min_cost){
            min_cost = tempCost;
            path = tempPath;
        }
        tempPath.pop_back();
        return;
    }

    for(int i=0; i<pre[u].size(); ++i){
        dfs(pre[u][i]);
    }
    tempPath.pop_back();
}

void diji(int s){
    pre[s].push_back(s);
    dis[s] = 0;
    for(int i=0; i<n; ++i){
        int u=-1, minn = inf;
        for(int j=0; j<n; ++j){
            if(visit[j] == false && dis[j] < minn){
                u = j;
                minn = dis[j];
            }
        }
        if(u == -1) return ;
        visit[u] = true;
        for(int v=0; v<n; ++v){
            if(visit[v] == false && e[u][v] != inf){
                if(dis[v] > dis[u] + e[u][v]){
                    dis[v] = dis[u] + e[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                }
                else if(dis[v] == dis[u] + e[u][v]){
                    pre[v].push_back(u);
                }
            }
        }
    }
}

int main(){
    fill(e[0], e[0]+510*510, inf);
    fill(dis, dis+510, inf);
    cin>>n>>m>>s>>d;
    for(int i=0; i<m; ++i){
        int z,x,c,v;
        cin>>z>>x>>c>>v;
        e[z][x] = e[x][z] = c;
        cost[z][x] = cost[x][z] = v;
    }
    diji(s);
    dfs(d);
    for(int i=path.size()-1; i>=0; --i){
        cout<<path[i]<<' ';
    }
    cout<<dis[d]<<' '<<min_cost;
    return 0;

}
