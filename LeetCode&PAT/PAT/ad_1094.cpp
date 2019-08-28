// 层次遍历，节点数最多的层

#include<vector>
#include<iostream>

using namespace std;

// 简便表示树 node[index] : index 为节点的index , node[index]存储子节点
//                          的index
vector<int> node[100];
int level_cnt[100];

int level = 1, cnt = 1;

void dfs(int index, int level){
    level_cnt[level]++;
    for(int i=0; i<node[index].size(); ++i){
        dfs(node[index][i],level+1);
    }
}

int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0; i<m;++i){
        int id, cnt_i;
        cin>>id>>cnt_i;
        for(int j=0;j<cnt_i;++j){
            int temp;
            cin>>temp;
            node[id].push_back(temp);
        }
    }
    dfs(1,1);
    for(int i=1;i<=n;++i){
        if(cnt < level_cnt[i]){
            level = i;
            cnt = level_cnt[i];
        }
    }

    cout<<cnt<<" "<<level;
    return 0;

}