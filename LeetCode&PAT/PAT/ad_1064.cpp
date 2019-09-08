#include<cstdio>
#include<algorithm>

using namespace std;
const int maxn = 1010;
int n, numbers[maxn], CBT[maxn], index=0;

void inOrder(int root){
    if(root > n) return;
    inOrder(root*2);
    CBT[root] = numbers[index++];
    inOrder(root*2+1);
}

int main(){
    scanf("%d",&n);
    for(int i=0; i<n; ++i){
        scanf("%d",&numbers[i]);
    }
    sort(numbers,numbers+n);
    inOrder(1);
    for(int i=1; i<=n; ++i){
        printf("%d",CBT[i]);
        if(i < n) printf(" ");
    }
    return 0;
}