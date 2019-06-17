#include<iostream>

int main(){
    int m ;
    std::cin>>m;
    int bai = m/100;
    int ge = m%10;
    int shi = (m-bai*100-ge)/10;
    for(int i=0;i<bai;i++){
        std::cout<<'B';
    }
    for(int i=0;i<shi;i++){
        std::cout<<'S';
    }
    for(int i=1;i<=ge;i++){
        std::cout<<i;
    }
    return 1;
}