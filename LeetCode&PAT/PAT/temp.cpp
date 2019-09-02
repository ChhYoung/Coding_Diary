#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int n, maxheight = 0;
// 邻接表
vector<vector<int>> v;
// 记录是否已经访问
bool visit[10010];

set<int> s;
// temp 用来临时存放找到的最远节点
vector<int> temp;

void dfs(int node, int height){
    if(height > maxheight){
        temp.clear();
        temp.push_back(node);
        maxheight = height;
    }
    else if(height == maxheight){
        temp.push_back(node);
    }

    visit[node] = true;
    for(int i=0;i<v[node].size();++i){
        if(visit[v[node][i]] == false){
            dfs(v[node][i],height+1);
        }
    }
}

int main(){
    scanf("%d",&n);
    v.resize(n+1);
    int a,b, cnt=0, s1=0;
    // 输入邻接表
    for(int i=0;i<n-1;++i){
        scanf("%d %d",&a,&b);
        v[a].push_back(b);
        v[b].push_back(a);
    }

    for(int i=1;i<=n; ++i){
        if(visit[i] == false){
            dfs(i,1);
            if(i == 1){
                // 记录第一次dfs中找到的最小的节点 s1，用来作为第二次dfs的开头
                if(temp.size() != 0) s1 = temp[0];
                // 记录所有第一次找到的节点
                for(int j=0; j<temp.size(); ++j)
                    s.insert(temp[j]);
            }
            // 记录连通域数量
            cnt++;
        }
    }

    if(cnt>=2){
        printf("Error: %d components",cnt);
    }
    else{
        // 第二次 dfs
        temp.clear();
        maxheight = 0;
        fill(visit, visit+10010,false);
        dfs(s1,1);
        for(int i=0; i<temp.size(); ++i){
            s.insert(temp[i]);
        }
        for(auto it=s.begin(); it != s.end(); ++it)
            printf("%d\n",*it);
    }
    return 0;
}