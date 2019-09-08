#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
using namespace std;
const int maxn = 40;

struct node{
    int data;
    node *left,*right;
};

vector<int> post, inorder;
vector<node*> tree;
vector<int> res;


/*
postL  --------- postR
inL--------------inR
*/


// 由后序和中序序列构造二叉树
node* createTree(int postL, int postR, int inL, int inR){
    if(postL > postR) return nullptr;
    node* root = new node;
    root->data = post[postR];
    int k;
    for(k=inL; k<=inR; ++k){
        if(inorder[k] == post[postR]){
            break;
        }
    }
    int numL = k - inL;
    root->left  = createTree(postL,postL+numL-1, inL,inL+numL-1);
    root->right = createTree(postL+numL,postR-1,inL+numL+1, inR);
    return root;
}

// 层次遍历
void bfs(node* root){
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        node* &ptr = q.front();
        q.pop();
        res.push_back(ptr->data);
        if(ptr->left) q.push(ptr->left);
        if(ptr->right) q.push(ptr->right);
    }
}

int main(){
    int n;
    cin>>n;
    post.resize(n);
    inorder.resize(n);
    tree.resize(n);
    for(int i=0; i<n; ++i) cin>>post[i];
    for(int i=0; i<n; ++i) cin>>inorder[i];
    // 构建二叉树
    auto root = createTree(0,n-1,0,n-1);
    // 层次遍历
    bfs(root);
    for(int i=0;i<res.size();++i){
        cout<<res[i];
        if(i != res.size()-1) cout<<' ';
    }
    return 0;
}