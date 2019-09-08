#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

struct node{
    int data;
    node *left=nullptr, *right=nullptr;
};

vector<node> tree;
vector<int> vec;

int N;

int num = 0;
void trav_in(node* a){
    if(a == nullptr) return;
    trav_in(a->left);
    a->data = vec[num++];
    trav_in(a->right);
}

void trav_level(node* root){
    int index = 1;
    queue<node*> q;
    q.push(root);
    while(!q.empty()){
        auto ptr = q.front();
        cout<<ptr->data;
        if((index++) != N) cout<<' ';
        q.pop();
        if(ptr->left) q.push(ptr->left);
        if(ptr->right) q.push(ptr->right);
    }
}

int main(){
    // 初始化
    cin>>N;
    tree.resize(N);
    vec.resize(N);
    for(int i=0; i<N; ++i){
        int a,b;
        cin>>a>>b;
        if(a != -1) tree[i].left = &tree[a];
        if(b != -1) tree[i].right = &tree[b];
    }
    for(int i=0; i<N; ++i){
        cin>>vec[i];
    }
    sort(vec.begin(), vec.end());
    trav_in(&tree[0]);
    trav_level(&tree[0]);
    return 0;
}

