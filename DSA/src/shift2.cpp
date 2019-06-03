#include<algorithm>
#include<iostream>

void shift2(int*A ,int n,int k){
    std::reverse(A,A[k]);
    std::reverse(A+k,n-k);
    std::reverse(A,n);
}

int main(){
   int A[5]{1,2,3,4,5};
   shift2(A,5,2);
   for(int i=0;i<5;i++)
       std::cout<<A[i]<<std::endl;
    return 0;
}