#include<iostream>
#include<algorithm>

using namespace std;
const int maxn = 1010;

int n, numbers[maxn], tree[maxn], index=0;

void inOrder(int root){
    if(root > n) return ;
    inOrder(2*root);
    tree[root] = numbers[index++];
    inOrder(2*root + 1);
}

int main(){
    cin>>n;
    for(int i=0; i<n; ++i){
        cin>>numbers[i];
    }
    sort(numbers,numbers + n);
    inOrder(1);
    for(int i=1; i<=n; ++i){
        cout<<tree[i];
        if(i != n) cout<<' ';
    }
    return 0;
}


