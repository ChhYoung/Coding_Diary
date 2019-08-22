#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
const int inf = 99999999;
struct station {
    double price,dis;
};

bool cmp1(station a, station b){
    return a.dis < b.dis;
}

int main(){
    double cmax,d,davg;
    int n;
    scanf("%lf %lf %lf %d",&cmax,&d,&davg,&n);
    vector<station> sta(n+1);
    sta[0] = {0.0,d};
    for(int i=1;i<=n;++i){
        scanf("%lf %lf",&sta[i].price, &sta[i].dis);
    }
    sort(sta.begin(),sta.end(),cmp1);
    // leftdis 剩余油能开的距离
    double nowdis = 0.0,maxdis = 0.0,nowprice = 0.0,totalPrice = 0.0, leftdis = 0.0;
    if(sta[0].dis != 0){
        printf("The maximum travel distance = 0.00");
        return 0;
    }
    else{
        nowprice = sta[0].price;
    }

    while(nowdis < d){
        // 到达最远距离的坐标
        maxdis = nowdis + cmax*davg;
        double minPriceDis = 0, minPrice = inf;
        int flag = 0;
        for(int i=1;i<=n && sta[i].dis <= maxdis;++i){
            if(sta[i].dis <= nowdis) continue;
            // 找到最近的比当前油价第的加油站
            // 加刚好抵达的油: 距离要的油 - 邮箱剩余的油
            if(sta[i].price < nowprice){
                totalPrice += (sta[i].dis - nowdis - leftdis)*nowprice/davg;
                // 到达加油站，更新变量
                leftdis = 0.0;
                nowprice = sta[i].price;
                nowdis = sta[i].dis;
                flag = 1;
                break;
            }
            // 更新最小油价
            if(sta[i].price < minPrice){
                minPrice = sta[i].price;
                minPriceDis = sta[i].dis;
            }
        }
        // 在距离内的油价都大于当前油价
        // 找到其中价格最低的，在当前加油站把油拉满
        if(flag == 0 && minPrice != inf ){
            totalPrice += (nowprice *(cmax - leftdis/davg));
            leftdis = cmax * davg - (minPriceDis - nowdis);
            nowprice = minPrice;
            nowdis = minPriceDis;
        }
        // 距离范围内没加油站，不能到达
        if(flag == 0 && minPrice == inf){
            nowdis += cmax*davg;
            printf("The maximum travel distance = %.2f",nowdis);
            return 0;
        }
    }
    printf("%.2f",totalPrice);
    return 0;

}