#include<string>
#include<iostream>
#include <cctype>

using namespace std;
int main(){
    
    string str1,str2,str3,str4;
    cin>>str1;
    cin>>str2;
    cin>>str3;
    cin>>str4;/* 
    string str1={"03485djDkxh4hhGN"};
    string str2={"02984akDfkkkkggNdsb"};
    string str3={"s&hgefensfdk"};
    string str4={"d&Hyscvnm"};*/
    for(int i=0;i<min(str1.length(),str2.length());i++){
        if(str1[i]==str2[i] && str1[i]>='A' && str1[i]<='G'){
            switch (str1[i])
            {
            case 'A': cout<<"MON ";break;
            case 'B': cout<<"TUE ";break;
            case 'C': cout<<"WED ";break;
            case 'D': cout<<"THU ";break;
            case 'E': cout<<"FRI ";break;
            case 'F': cout<<"SAT ";break;
            case 'G': cout<<"SUN ";break;
            }
            for(int j=i+1;j<min(str1.length(),str2.length());j++){
                if(str1[j]==str2[j]){
                    if(str1[j]>='0' && str1[j]<='9'){
                        cout<<0<<str1[j];
                        cout<<":";
                        break;
                    }
                    else if(str1[j]>='A' && str1[j]<='N'){
                        cout<<(str1[j]-'A'+10);
                        cout<<":";
                        break;
                    }
                    
                }
            }
            break;
        }
    }
    for(int i=0;i<min(str3.length(),str4.length());i++){
        if(str3[i]==str4[i] && isalpha(str3[i])){
            if(i>=0 && i<=9){
                        cout<<0<<i;
            }
            else
            {
                cout<<i;
            }
            break;
        }
    }


    return 0;
}
