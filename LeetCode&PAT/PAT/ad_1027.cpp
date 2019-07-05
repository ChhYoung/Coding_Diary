#include<iostream>
using namespace std;
void my_func(int a,int b){
    switch(a){
        case 0: cout<<0;break;
        case 1: cout<<1;break;
        case 2: cout<<2;break;
        case 3: cout<<3;break;
        case 4: cout<<4;break;
        case 5: cout<<5;break;
        case 6: cout<<6;break;
        case 7: cout<<7;break;
        case 8: cout<<8;break;
        case 9: cout<<9;break;
        case 10: cout<<'A';break;
        case 11: cout<<'B';break;
        case 12: cout<<'C';break;
    }
    switch(b){
        case 0: cout<<0;break;
        case 1: cout<<1;break;
        case 2: cout<<2;break;
        case 3: cout<<3;break;
        case 4: cout<<4;break;
        case 5: cout<<5;break;
        case 6: cout<<6;break;
        case 7: cout<<7;break;
        case 8: cout<<8;break;
        case 9: cout<<9;break;
        case 10: cout<<'A';break;
        case 11: cout<<'B';break;
        case 12: cout<<'C';break;
    }
}

int main(){
    int a,b,c;
    cin>>a>>b>>c;
    cout<<'#';
    my_func(a/13,a%13);my_func(b/13,b%13);my_func(c/13,c%13);
    return 0;
}