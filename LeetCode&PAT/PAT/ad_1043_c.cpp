#include<vector>
#include<iostream>
using namespace std;

struct node{   
    int data;
    node *left, *right;
};

vector<int> origin, pre, post, preMi, postMi;

void insert(node* &root, int data){
    if(root == nullptr){
        root = new node;
        root->data = data;
        root->left = root->right = nullptr;
        return;
    }

    if(data < root->data) insert(root->left,data);
    else insert(root->right, data);
}

void trav_pre(node* root){
    if(root == nullptr) return;
    pre.push_back(root->data);
    trav_pre(root->left);
    trav_pre(root->right);
}

void trav_post(node* root){
    if(root == nullptr) return;
    trav_post(root->left);
    trav_post(root->right);
    post.push_back(root->data);
}

void trav_pre_mi(node* root){
    if(root == nullptr) return;
    preMi.push_back(root->data);
    trav_pre_mi(root->right);
    trav_pre_mi(root->left);
}

void trav_post_mi(node* root){
    if(root == nullptr) return;
    trav_post_mi(root->right);
    trav_post_mi(root->left);
    postMi.push_back(root->data);
}



int main(){
    
    int n,data;
    cin>>n;
    node* root = nullptr;
    for(int i=0; i<n; ++i){
        cin>>data;
        origin.push_back(data);
        insert(root,data);
    }

    trav_pre(root);
    trav_pre_mi(root);
    
    
    if(origin == pre){
        trav_post(root);
        cout<<"YES\n";
        for(int j=0; j<post.size(); j++){
            cout<<post[j];
            if(j < post.size()-1) cout<<' ';
        }
    } else if(origin == preMi){
        trav_post_mi(root);
        cout<<"YES\n";
        for(int j=0; j<postMi.size(); j++){
            cout<<postMi[j];
            if(j < postMi.size()-1) cout<<' ';
        }
    } else {
        cout<<"NO";
    }

    return 0;
}
