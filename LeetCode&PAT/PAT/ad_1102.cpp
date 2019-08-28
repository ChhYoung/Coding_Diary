#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
struct node{
    int id,l,r,index,level;
}a[100];
// 右左中序遍历
vector<node> v1;
void in_and_dfs(int root, int index,int level){
    if(a[root].r != -1) in_and_dfs(a[root].r, index*2+2, level+1);
    v1.push_back({root,0,0,index,level});
    if(a[root].l != -1) in_and_dfs(a[root].l, index*2+1, level+1);
}

bool cmp(node a,node b){
    if(a.level != b.level) return a.level < b.level;
    return a.index > b.index;
}

int main(){
    int n, have_child[100]={0}, root=0;
    cin>>n;
    for(int i=0; i<n; ++i){
        a[i].id = i;
        string l,r;
        cin>>l>>r;
        if(l != "-"){
            a[i].l = stoi(l);
            have_child[stoi(l)] = 1;
        }
        else{
            a[i].l = -1;
        }
        if(r != "-"){
            a[i].r = stoi(r);
            have_child[stoi(r)] = 1;
        }
        else{
            a[i].r = -1;
        }
    }

    while(have_child[root] == 1) root++;
    in_and_dfs(root,0,0);
    vector<node> v2(v1);
    sort(v2.begin(),v2.end(),cmp);
    for(int i=0;i<v2.size();++i){
        if(i != 0) cout<<' ';
        cout<<v2[i].id;
    } 
    cout<<endl;
    for(int i=0;i<v1.size();++i){
        if(i != 0) cout<<' ';
        cout<<v1[i].id;
    }
    return 0;
}