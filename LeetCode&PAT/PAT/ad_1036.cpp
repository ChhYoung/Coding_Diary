#include<iostream>
#include<string>
using namespace std;
int main(){
    string name,id,name_girl,name_boy,girl_id,boy_id;
    char gender;
    int grade,boy_grade = 101, girl_grade = -1;
    int N;
    cin>>N;
    for(int i=0;i<N;++i){
        cin>>name>>gender>>id>>grade;
        if(gender == 'M'){
            if(grade < boy_grade){
                boy_grade = grade;
                name_boy = name;
                boy_id = id;
            }
        }
        else{
            if(grade > girl_grade){
                girl_grade = grade;
                name_girl = name;
                girl_id = id;
            }
        }
    }
    if(boy_grade == 101 || girl_grade == -1){
        if(boy_grade == 101){
            cout<<name_girl<<' '<<girl_id<<"\n"<<"Absent\n"<<"NA";
        }
        else {
            cout<<"Absent\n"<<name_boy<<' '<<boy_id<<"\n"<<"NA";
        }

    }
    else{
        cout<<name_girl<<' '<<girl_id<<"\n";
        cout<<name_boy<<' '<<boy_id<<"\n";
        cout<<girl_grade - boy_grade;
    }
    return 0;
}