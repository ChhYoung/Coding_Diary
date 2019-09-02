#include<iostream>
#include<map>
#include<string>

using namespace std;

map<string,int> stringToInt,ans;
map<int,string> intToString;

int G[2010][2010], weight[2010];
bool vis[2010];

// 通过dfs访问每个联通块
void dfs(int u, int &head, int &numMember, int &totalWeight){
    vis[u] = true;
    numMember++;
    
}