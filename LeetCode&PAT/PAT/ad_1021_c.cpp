#include<iostream>
#include<vector>
#include<algorithm>
#include<set> // 存储第一次dfs得到的节点,有序
using namespace std;
int n,maxHeight = 0;
//邻接表
vector<vector<int>> v;
bool visit[10010];
set<int> s;
// 存储临时的最远节点
vector<int> temp;

void dfs(int node, int height){
    if(height > maxHeight){
        maxHeight = height;
        temp.clear();
        temp.push_back(node);
    } else if(height == maxHeight){
        temp.push_back(node);
    }
    visit[node] = true;
    for(int i=0; i<v[node].size(); ++i){
        if(visit[v[node][i]] == false)
            dfs(v[node][i],height+1);
    }
}

int main(){
    cin>>n;
    v.resize(n+1);
    for(int i=0; i<n-1; ++i){
        int a,b;
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    // 第一次dfs找到遍历一次时最深的节点，
    // 并判断是否有多个连通域
    int s1=0,cnt=0;
    for(int i=1; i<=n; ++i){
        if(visit[i] == false){
            dfs(i,1);
            if(i == 1){
                if(temp.size() != 0) s1 = temp[0];
                for(int j=0; j<temp.size(); ++j)
                    s.insert(temp[j]);
            }
            cnt++;
        }
    }

    if(cnt>=2){
        printf("Error: %d components",cnt);
    }
    else {
        temp.clear();
        maxHeight = 0;
        fill(visit, visit+10010, false);
        dfs(s1, 1);
        for(int i=0; i<temp.size(); ++i)
            s.insert(temp[i]);
        for(auto it=s.begin(); it != s.end(); ++it)
            cout<<*it<<endl;
    }
    return 0;
}
