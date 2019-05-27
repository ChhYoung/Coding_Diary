# PAT

##  乙级

###  1001害死人不偿命的(3n+1)猜想(15分)

**得分 15/15**

```C++
#include<iostream>
using namespace std;
int main(){
    int n;
    int count = 0;
    cin>>n;
    while(n > 1){
        if(n%2 == 0){
            n /= 2;
            ++count;
            continue;
        }
        else{
            n = 3*n + 1;
            continue;
        }
    }
    cout<<count;
    return 0;
}
```

### 1002写出这个数(20分)

**20/20**

```C++
#include<iostram>
#include<string>
using namespace std;
int main(){
    int sum = 0;
    string s;
    string str[10]{ "ling","yi","er","san","si",
					"wu","liu","qi","ba","jiu" };
    cin<<s;
    const int legth = s.length();
    for(int i = 0;i < length;++i){
        sum += (s[i] - '0');
    }
    string num = to_string(sum);
    for(int i = 0;i < num.length(); ++i){
        if (i!=0)
            cout<<" ";
        cout << str[num[i] - '0'];
    }
    return 0;
}
```
### 1004 成绩排名 (20 分)

```c++
#include<iostream>
#include<string>

using namespace std;
int main(){
    int n,score;
    int max = -1,min = 101; 
    string name,sno,max_name,max_sno,min_name,min_sno;
    cin>>n;
    for(int i=0;i<n;++i){
        cin>>name>>sno>>score;
        if(score > max){
            max = score;
            max_name = name;
            max_sno =sno;
        }
        if(score < min){
            min = score;
            min_name = name;
            min_sno =sno;
        }
    }
    cout<<max_name<<" "<<max_sno<<"\n";
    cout<<min_name<<" "<<min_sno;
    return 0;
}
```
