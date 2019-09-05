#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<map>

using namespace std;

const int maxv = 210;
const int inf = 99999999;

int n, m, st, G[maxv][maxv], weight[maxv];
int d[maxv], numPath=0, maxW=0;
double maxAvg = 0;
bool visit[maxv] = {false};
vector<int> pre[maxv];
vector<int> tempPath, path;
map<string, int> strToInt;
map<int, string> IntToString;

void diji(int s){
    fill(d, d+maxv, inf);
    d[s] = 0;
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
                if(d[v] > d[u] + G[u][v]){
                    d[v] = d[u] + G[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                }
                else if(d[v] > d[u] + G[u][v]){
                    pre[v].push_back(u);
                }
            }
        }
    }
}


void dfs(int v){
    // 每次一条路 入栈，出栈完，然后向上层返回到有多分枝的节点，继续向下访问
    tempPath.push_back(v);
    // 递归边界
    if(v == st){
        numPath++;
        int tempW = 0;
        //倒着访问，计算点权
        for(int i=tempPath.size()-2; i>=0; i--){
            int id = tempPath[i];
            tempW += weight[id];
        }
        double tempAvg = 1.0 * tempW / (tempPath.size() - 1);
        if(tempW > maxW){
            maxW = tempW;
            path = tempPath;
            maxAvg = tempAvg;
        }
        else if(tempW == maxW && tempAvg > maxAvg){
            maxAvg = tempAvg;
            path = tempPath;
        }
        tempPath.pop_back();
        return;
    }
    
    for(int i=0; i<pre[v].size(); ++i){
        dfs(pre[v][i]);
    }
    tempPath.pop_back();
}
