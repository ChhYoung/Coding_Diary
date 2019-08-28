// N : 节点总数   0 - N-1;   P : unit price ;  r : rate
// K_i : total number receive products from i 子节点个数
// k_i == 0 --->  i is a retailer , the amonut of its product 
//      is given 

#include<cstdio>
#include<vector>
#include<cmath>

using namespace std;

struct node{
    // 倍数
    double data;
    // 子节点的index
    vector<int> child;
};

vector<node> v;
double ans = 0.0, p, r;

void dfs(int index, int depth){
    if(v[index].child.size() == 0){
        ans += v[index].data*pow(1+r,depth);
        return ;
    }
    for(int i=0; i<v[index].child.size();++i){
        dfs(v[index].child[i],depth+1);
    }
}

int main(){
    int n,k,c;
    scanf("%d %lf %lf",&n,&p,&r);
    r = r/100;
    v.resize(n);
    for(int i=0; i<n; ++i){
        scanf("%d",&k);
        if(k==0){
            scanf("%lf",&v[i].data);
        }
        else{
            for(int j=0;j<k; ++j){
                scanf("%d",&c);
                v[i].child.push_back(c);
            }
        }
    }
    dfs(0,0);
    printf("%.1f",ans*p);
    return 0;
}