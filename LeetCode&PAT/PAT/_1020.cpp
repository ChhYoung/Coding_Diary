#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct mooncake{
    float mount,price,unit;
};
int cmp(mooncake a,mooncake b){
    return a.unit>b.unit;
}
int main(){
    int n,need;
    cin>>n>>need;
    vector<mooncake> a(n);
    for(int i=0;i<n;i++) scanf("%f",&a[i].mount);
    for(int i=0;i<n;i++) scanf("%f",&a[i].price);
    for(int i=0;i<n;i++) a[i].unit = a[i].price/a[i].mount;
    sort(a.begin(),a.end(),cmp);
    float res = 0.0;
    for(int i=0;i<n;++i){
        if(a[i].mount<=need){
            res = res + a[i].price;
        }
        else{
            res = res + a[i].unit*need;
            break;
        }
        need -= a[i].mount;
    }
    printf("%.2f",res);
    return 0;
}