#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

int n,k,p,maxFacSum = -1;
vector<int> v,ans,tempAns;

// 初始化Fac数组，当i^p小于n时不断把i^p加入数组
// 创建一个备选数数组v
void init(){
    int temp = 0,index = 1;
    while(temp <= n){
        v.push_back(temp);
        temp = pow(index,p);
        index++;
    }
}

// dfs函数
// 当前访问fac[index] ， tempK为当前选中的数
// tempSum 为当前选中的数的幂之和 ， facSum 为当前选中的底数之和
void dfs(int index, int tempSum, int tempK, int facSum){
    // 递归基，当满足条件时
    if(tempK == k){
        if(tempSum == n && facSum > maxFacSum){
            ans = tempAns;
            maxFacSum = facSum;
        }
        return;
    }
    while(index >= 1){
        // 继续在v中寻找满足条件的数
        if(tempSum + v[index] <= n){
            tempAns[tempK] = index;
            dfs(index,tempSum+v[index],tempK+1,facSum+index);
        }
        // 不产生答案直接返回
        if(index == 1) return ;
        // 当前fac[index]不行，找下一个
        index--;
    }
}

int main(){
    scanf("%d %d %d",&n,&k,&p);
    init();
    tempAns.resize(k);
    dfs(v.size()-1,0,0,0);
    if(maxFacSum == -1){
        printf("Impossible");
        return 0;
    }
    printf("%d = ",n);
    for(int i=0; i<ans.size();++i){
        if(i != 0) printf(" + ");
        printf("%d^%d",ans[i],p);
    }
    return 0;
}



