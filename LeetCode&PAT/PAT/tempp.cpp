#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
const int N = 10010;
int father[N];

void init(int n){
    for(int i=1; i<=n; ++i){
        father[i] = i;
    }
}


int findFather(int x){
    int a = x;
    while(x != father[x])
        x = father[x];
    while( a != father[a]){
        int z = a;
        father[z] = x;
    }
    return x;
}

void Union(int a, int b){
    int faA = findFather(a);
    int faB = findFather(b);
    if(faA != faB){
        father[faA] = faB;
    }
}\

const int maxv = 10000;
const int inf = 1000000;
int n, G[maxv][maxv],d[maxv];
bool visit[maxv];
int prim(){
    fill(d,d+maxv,inf);
    d[0] = 0;
    int ans = 0;
    for(int i=0; i<n; ++i){
        int u=-1, minn = inf;
        for(int j=0; j<n; ++j){
            if(visit[j] == false && d[j] < minn){
                u = j;
                minn = d[j];
            }
        }
        if(u == -1) return -1;
        visit[u] = true;
        ans += d[u];
        for(int v=0; v<n; ++v){
            if(visit[v]==false && G[u][v] != inf && G[u][v] < d[v]) {
                d[v] = G[u][v];
            }
        }
    }
    return ans;
}

const int maxn = 100;
int heap[maxn], n=10;

void down_adjust(int low, int high){
    int i=low, j=2*i;
    while(j <= high){
        if(j+1 <= high && heap[j+1] > heap[j]){
            j += 1;
        }

        if(heap[j] > heap[i]){
            swap(heap[j], heap[i]);
            i = j;
            j = 2*i;
        }
        else{
            break;
        }
    }
}

void createHeap(){
    for(int i=n/2; i>=1; i--){
        down_adjust(i,n);
    }
}

