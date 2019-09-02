#include<cstdio>
#include<algorithm>
using namespace std;
struct node{
    int v,height;
    node *left,*right;
}*root;

node* newNode(int v){
    node* Node = new node;
    Node->v = v;
    Node->height = 1;
    Node->left = Node->right = nullptr;
    return Node;
}

int getHeight(node* root){
    if(root == nullptr) return 0;
    return root->height;
}

void updateHeight(node* root){
    root->height = max(getHeight(root->left),getHeight(root->right))+1;
}

int getBalancedFactor(node* root){
    return getHeight(root->left)-getHeight(root->right);
}

// zag
void L(node* &root){
    node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}

// zig
void R(node* &root){
    node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    updateHeight(root);
    updateHeight(temp);
    root = temp;
}

void insert(node* &root, int v){
    if(root == nullptr){
        root = newNode(v);
        return;
    }

    if(v < root->v){
        insert(root->left, v);
        updateHeight(root);
        if(getBalancedFactor(root) == 2){
            if(getBalancedFactor(root->left) == 1){
                R(root);
            }
            else if(getBalancedFactor(root->left) == -1){
                L(root->left);
                R(root);
            }
        }
    }
    else{
        insert(root->right, v);
        updateHeight(root);
        if(getBalancedFactor(root) == -2){
            if(getBalancedFactor(root->right) == -1){
                L(root);
            }
            else if(getBalancedFactor(root->right) == 1){
                R(root->right);
                L(root);
            }
        }
    }
}

node* Create(int data[], int n){
    node* root = nullptr;
    for(int i=0; i<n; ++i){
        insert(root,data[i]);
    }
    return root;
}

int main(){
    int n,v;
    scanf("%d", &n);
    //node* root = new node();
    for(int i=0;i<n;++i){
        scanf("%d",&v);
        insert(root,v);
    }
    printf("%d\n",root->v);
    return 0;
}
