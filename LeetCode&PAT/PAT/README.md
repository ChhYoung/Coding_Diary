# PAT

[TOC]



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

### 1006 换个格式输出整数(15 points)

```c++
#include<iostream>

int main(){
    int m ;
    std::cin>>m;
    int bai = m/100;
    int ge = m%10;
    int shi = (m-bai*100-ge)/10;
    for(int i=0;i<bai;i++)
        std::cout<<'B';
    for(int i=0;i<shi;i++)
        std::cout<<'S';
    for(int i=1;i<=ge;i++)
        std::cout<<i;
    return 0;
}
```

```c++

#include <iostream>
using namespace std;
int main() {
    int a, i = 0;
    cin >> a;
    int b[3] = {0};
    while (a != 0) {
        b[i++] = a % 10;
        a = a / 10;
    }
    for (int k = 0; k < b[2]; k++)
        cout << "B";
    for (int k = 0; k < b[1]; k++)
        cout << "S";
    for (int k = 0; k < b[0]; k++)
        cout << k + 1;
    return 0;
}
```

### 1007 素数对猜想

```c++
#include<iostream>
using namespace std;
bool isprime(int a){
    for(int i=2;i*i<=a;++i){
        if(a%i==0) return false;
    }
    return true;
}

int main(){
    int N,cnt=0;
    cin>>N;
    for(int i=5;i<=N;i++)
        if(isprime(i-2) && isprime(i)) cnt++;
    cout<<cnt;
    return 0;
}
```

### 1008 数组右移

```c++
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    m %= n;
    if (m != 0) {
        reverse(begin(a), begin(a) + n);
        reverse(begin(a), begin(a) + m);
        reverse(begin(a) + m, begin(a) + n);
    }
    for (int i = 0; i < n - 1; i++)
        cout << a[i] << " ";
    cout << a[n - 1];
    return 0;
}
```

### 1009 说反话

```c++
#include <iostream>
#include<stack>
#include<string>

int main(){
    std::stack<std::string> v;
    std::string s;
    while(std::cin>>s) v.push(s);
    std::cout<<v.top();
    v.pop();
    while(!v.empty()){
        std::cout<<" "<<v.top();
        v.pop();
    }
    return 0;
}
```

### 1010 多项式求导

```c++
#include<iostream>
#include<vector>

using namespace std;

int main(){
    vector<int> k;
    int i;
    while(cin>>i)
        k.push_back(i);
    for(int i=0;i<k.size();i++){
        if(i%2==0)
            k[i] *= k[i+1];
    }
    for(int i=0;i<k.size();i++){
        if(i%2==1)
            k[i] -= 1;
    }
    for(int i=0;i<=k.size()-2;i+=2){
        if(k[0]==0 && k[1]==-1){
            cout<<0;
            break;
        }
        if(i != 0 && k[i+1]!=-1)
            cout<<" ";
        if(i%2 == 0 && k[i+1]!=-1){
            cout<<k[i]<<" "<<k[i+1];
        }
    }
    return 0;
}
```

```c++
#include<iostream>
using namespace std;
int main(){
    int a,b,flag=0;
    while(cin>>a>>b){
        if(b!=0){
            if(flag == 1) cout<<" ";
            cout<<a*b<<" "<<b-1;
            flag = 1;
        }
    }
    if(flag == 0) cout<<"0 0";
    return 0;
}
```

### 1013 数素数

```c++
#include<iostream>
#include<vector>
using namespace std;
bool isPrime(int a){
    for(int i=2;i*i<=a;i++){
        if(a%i == 0)
            return false;
    }
    return true;
}

int main(){
    int M,N,cnt=0;
    vector<int> res={2};
    cin>>M>>N;
    for(int j=3;res.size()<=N;j++){
        if(isPrime(j))
            res.push_back(j);
    }
    for(int k=M-1;k<N;k++){
        cnt++;
        cout<<res[k];
        //if(cnt==1) cout<<" ";
        if(cnt%10 == 0 && k != N-1) cout<<"\n";
        else if(k != N-1) cout<<" ";
        else if(k == N-1) cout<<"\n";
    }
    return 0;
}
```



## 甲级

### 1001 A+B format (20 points)

```c++
#include<iostream>
#include<string>
using namespace std;
int main(){
    int a,b;
    cin>>a>>b;
    string s = to_string(a+b);
    int len = s.length();
    for(int i=0;i<len;i++){
        cout<<s[i];
        if(s[i] == '-') continue;
        if((i+1)%3 == len%3 && i != len-1)
            cout<<",";
    }
    return 0;
}
```

### 1002 A+B for Polynomials **(25** point(s))

利用好C语言中的数据输入输出函数，内存不要扣得太紧

```c++
#include <iostream>
using namespace std;
int main() {
    float c[1001] = {0};
    int m, n, t;
    float num;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%d%f", &t, &num);
        c[t] += num;
    }
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d%f", &t, &num);
        c[t] += num;
    }
    int cnt = 0;
    for (int i = 0; i < 1001; i++) {
        if (c[i] != 0) cnt++;
    }
    printf("%d", cnt);
    for (int i = 1000; i >= 0; i--) {
        if (c[i] != 0.0)
            printf(" %d %.1f", i, c[i]);
    }
    return 0;
}
```

### 1003. Emergency 25 points

N,M,C_1,