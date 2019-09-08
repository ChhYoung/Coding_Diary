#include<iostream>
#include<string>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 110;

struct node{
    int leftid;
    int rightid;
}NODE[maxn];

bool isRoot[maxn] = {false};
int n,num = 0;

void print(int id){
    cout<<id;
    num++;
    if(num < n) cout<<' ';
    else cout<<'\n';
}

void inOrder(int root){
    if(root == -1) return;
    inOrder(NODE[root].rightid);
    print(root);
    inOrder(NODE[root].leftid);
}

void level(int root){
    queue<int> q;
    q.push(root);
    while(!q.empty()){
        int now = q.front();
        q.pop();
        print(now);
        if(NODE[now].rightid != -1) q.push(NODE[now].rightid);
        if(NODE[now].leftid != -1)  q.push(NODE[now].leftid);
    }
}

int str2num(char c){
    return c == '-' ? -1 : c-'0';
}

int main(){
    cin>>n;
    for(int i=0; i<n; ++i){
        char a,b;
        cin>>a>>b;
        NODE[i].leftid = str2num(a);
        NODE[i].rightid = str2num(b);
        isRoot[NODE[i].leftid]=isRoot[NODE[i].rightid]=true;
    }
    int root = 0;
    for(;root<n; root++){
        if(isRoot[root] == false) break;
    }
    level(root);
    num = 0;
    inOrder(root);
    return 0;
}