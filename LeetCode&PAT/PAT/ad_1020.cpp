#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct  node{
    int index;
    int value;
};


bool cmp(node a, node b){
    return a.index < b.index;
}

vector<int> post,in;
vector<node> ans;

// 由后序，及中序得到先序
// root : post 中根在的位置
// start，end : 中序子树的首尾
// index : 层次遍历，用index为其在满树的位置
void pre(int root,int start,int end,int index){
    if(start > end) return;
    int i = start;
    // 找到 post[root] 即根在中序中的位置
    while(i < end && in[i] != post[root]){
        ++i;
    }
    ans.push_back({index,post[root]});
    // 中序中得右树的长度(end - i)，后序中找到左树的根(root-(end-i)-1)
    pre(root-1-end+i, start, i-1, 2*index+1);
    pre(root-1, i+1, end, 2*index+2);
}

int main(){
    int n=7;//int n ;
    //scanf("%d",&n);
    post.resize(n);
    in.resize(n);
    int a[7] = {2,3,1,5,7,6,4};
    int b[7] = {1,2,3,4,5,6,7};
    for(int i=0;i<n;++i) post[i]=a[i];//scanf("%d",&post[i]);
    for(int i=0;i<n;++i) in[i]=b[i];//scanf("%d",&in[i]);
    pre(n-1,0,n-1,0);
    sort(ans.begin(),ans.end(),cmp);
    for(int i=0;i<ans.size();++i){
        if(i !=0 ) cout<<" ";
        cout<<ans[i].value<<'.'<<ans[i].index;
    }
    return 0;

}