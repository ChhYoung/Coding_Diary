#include<cstdio>
#include<vector>
using namespace std;
bool isMiroor
;
vector<int> pre, post;
// INPUT: 先序 是否等于输入顺序   8 6 5 7 10 8 11
 
// 在先序中找到 左右子树
void getpost(int root, int tail){
    if(root > tail) return;
    int i = root+1, j=tail;
    // i 右子树的第一个节点 （ 10 ）
    // j 左子树的最右节点
    if(!isMiroor){
        while(i <= tail && pre[root] > pre[i]) i++;
        while(j > root && pre[root] <= pre[j]) j--;
    }
    else{
        while(i <= tail && pre[root] <= pre[i]) i++;
        while(j > root && pre[root] > pre[j]) j--;
    }
    if(i-j != 1) return ;
    getpost(root+1, j);
    getpost(i,tail);
    post.push_back(pre[root]);
}


int main(){
    int n;
    scanf("%d",&n);
    pre.resize(n);
    for(int i=0; i<n; ++i){
        scanf("%d",&pre[i]);
    }
    getpost(0, n-1);
    // 检查是否是mirror，如果是，则用mirror模式来进行
    if(post.size() != n){
        isMiroor = true;
        post.clear();
        getpost(0, n-1);
    }

    if(post.size() == n){
        printf("YES\n%d",post[0]);
        for(int i=1; i<n; ++i){
            printf(" %d",post[i]);
        }
    }
    else{
        printf("NO");
    }
    return 0;
}