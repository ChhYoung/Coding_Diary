
#include<cstring>
#include<cstdio>
#include<stack>
#include<vector>

using namespace std;

struct node{
    int value;
    node* rchild;
    node* lchild;
};

const int maxn = 50;
// 先中后序列
int pre[maxn],in[maxn],post[maxn];
// 节点个数
int n,num=0;


node* creat(int preL,int preR, int inL, int inR){
    if(preL > preR) return nullptr;
    node* root = new node;
    root->value = pre[preL];
    int k;
    for(k=inL; k<=inR; ++k){
        if(in[k] == pre[preL]){
            break;
        }
    }
    // 中序中左树的size 
    int numL = k - inL;
    root->lchild = creat(preL+1,preL+numL,inL,k-1);
    root->rchild = creat(preL+numL+1,preR,k+1,inR);
    return root;
}

void travPost(node* root){
    if(root == nullptr) return;
    travPost(root->lchild);
    travPost(root->rchild);
    printf("%d",root->value);
    ++num;
    if(num < n) printf(" ");
    return ;
}

int main(){
    scanf("%d",&n);
    char str[5];
    stack<int> st;
    
    int x,preIndex = 0,inIndex = 0;
    for(int i=0;i<2*n;++i){
        scanf("%s",str);
        if(strcmp(str,"Push") == 0){
            scanf("%d",&x);
            pre[preIndex++] = x;
            st.push(x);
        }
        else{
            in[inIndex++] = st.top();
            st.pop();
        }
    }

    node* root = creat(0,n-1,0,n-1);
    travPost(root);
    return 0;
}
