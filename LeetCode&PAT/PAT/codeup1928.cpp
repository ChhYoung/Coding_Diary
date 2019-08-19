#include<cstdio>

int month[13][2] = {{0,0},
        {31,31},{28,29},{31,31},{30,30},
        {31,31},{30,30},{31,31},{31,31},
        {30,30},{31,31},{30,30},{31,31}};

// 判断平年，闰年
bool isLeap(int year){
    return (year%4 == 0 && year % 100 !=0) || (year % 400 == 0);
}

int main(){
    int time1, y1, m1, d1;
    int time2, y2, m2, d2;
    while(scanf("%d%d",&time1,&time2) != EOF){
        if(time1 > time2){
            int temp = time1;
            time1 = time2;
            time2 = temp;
        }
    

        y1 = time1 / 10000; m1 = time1 % 10000/100; d1 = time1 % 100;
        y2 = time2 / 10000; m2 = time2 % 10000/100; d2 = time2 % 100;

        // 记录结果
        int ans = 1;
        // 在第一个日期没有达到第二个日期时循环
        while(y1<y2 || m1 < m2 || d1 < d2){
            // 天数加一
            ++d1;
            // 如果满当月天数
            if(d1 == month[m1][isLeap(y1)] + 1){
                ++m1;
                d1 = 1;
            }
            if(m1 == 13){
                y1 ++ ;
                m1 = 1;
            }
            ans ++;
        }
        printf("%d\n",ans);
    }
    return 0;
}