#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const int maxn = 1010;
const int inf = 9999999;
int n,m,k;
int lost_city;
vector<int> G[maxn];
bool visit[maxn];

// 利用dfs来搜说连通域的数量
void dfs(int v){
    if(v == lost_city) return;
    visit[v] = true;
    for(int i=0; i<G[v].size(); ++i){
        if(visit[G[v][i]] == false){
            dfs(G[v][i]);
        }
    }
}

int main(){
    
    cin>>n>>m>>k;
    for(int i=0; i<m; ++i){
        int a,b;
        cin>>a>>b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    for(int i=0; i<k; ++i){
        cin>>lost_city;
        int cnt = 0;
        fill(visit, visit+maxn, false);
        for(int j=1; j<=n; ++j){
            if(j != lost_city && visit[j] == false){
                dfs(j);
                cnt++;
            } 
        }
        cout<<cnt-1<<endl;
    }
    return 0;
}
