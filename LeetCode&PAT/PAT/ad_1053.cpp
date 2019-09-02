#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct node{
    int weight;
    vector<int> child;
}TREE[100];
// 存储路径
int path[100];
int N,M,S;

bool cmp(int a, int b){
    return TREE[a].weight > TREE[b].weight;
}

void dfs(int index, int nodeNum, int sum){
    if(sum > S) return ;
    else if(sum == S){
        if(TREE[index].child.size() != 0) return ;
        for(int i=0; i<nodeNum; ++i){
            printf("%d%c",TREE[path[i]].weight, i != nodeNum-1 ? ' ':'\n');
        }
        return;
    }
    else{
        for(int i=0; i<TREE[index].child.size(); ++i){
            int node = TREE[index].child[i];
            path[nodeNum] = node;
            dfs(node, nodeNum+1, sum+TREE[node].weight);
        }
    }
}

int main(){
    scanf("%d %d %d", &N,&M,&S);
    for(int i=0; i<N; ++i){
        cin>>TREE[i].weight;
    }
    for(int i=0; i<M; ++i){
        int id,k,child;
        cin>>id>>k;
        // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        TREE[id].child.resize(k);
        for(int j=0; j<k; ++j){
            cin>>TREE[id].child[j]; 
        }
        sort(TREE[id].child.begin(), TREE[id].child.end(), cmp);
    }
    path[0]=0;
    dfs(0,1,TREE[0].weight);
    return 0;

}