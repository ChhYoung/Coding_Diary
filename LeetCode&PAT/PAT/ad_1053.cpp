#include<iostream>
#include<vector>

using namespace std;

struct node{
    int weight;
    int index;
    vector<int> child;
}NODE[100];

int n,m,S;
// 用来存储路径
int path[100];
void dfs(int index,int numNode,int sum){
    if(sum > S) return ;
    if(sum == S){
        if(NODE[index].child.size() != 0) return;
        for(int i=0;i<NODE[index].child.size();++i){
            cout<<NODE[path[i]].weight;
            if(i < numNode -1) cout<<' ';
            else cout<<"\n";
        }
    }
    for(int i=0; i<NODE[index].child.size(); ++i){
        int child = NODE[index].child[i];
        path[numNode] = child;
        dfs(child, numNode+1, sum+NODE[index].weight);
    }
}
