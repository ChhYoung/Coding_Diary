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
            max_sno = sno;
        }
        if(score < min){
            min = score;
            min_name = name;
            min_sno = sno;
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

**求素数函数,素数的定义**

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

**可以将首位这种无规律的踢出循环**

```c++
#include <iostream>
#include<stack>
#include<string>

int main(){
    std::stack<std::string> v;
    std::string s;
    while(std::cin>>s) 
        v.push(s);
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

**设置标志位，来判断首尾**

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
        if(cnt%10 == 0 && k != N-1) cout<<"\n";
        else if(k != N-1) cout<<" ";
        else if(k == N-1) cout<<"\n";
    }
    return 0;
}
```

### 1016. 部分A+B

**原始方法： 放到int中再to_string**

```C++
#include<iostream>
#include<vector>
#include<string>

using namespace std;

int main(){
    int a,b,c,d;
    int cnt=0,res1=0,res2=0;
    cin>>a>>b>>c>>d;
    auto a1 = to_string(a);
    auto b1 = to_string(b);
    auto c1 = to_string(c);
    auto d1 = to_string(d);
    for(int i=0;i<a1.length();i++){
        if(a1[i] == b1[0]){
            cnt++;
        }
    }
    for(int j=1;j<=cnt;j++){
        res1 = 10*res1 + b;
    }
    cnt=0;
    for(int i=0;i<c1.length();i++){
        if(c1[i] == d1[0]){
            cnt++;
        }
    }
    for(int j=1;j<=cnt;j++){
        res2 = 10*res2 + d;
    }
    cout<<res1+res2;
    return 0;
}
```

**改进 : 将长的放到string中**

cin 同时写入不同的类型中

```c++
#include<iostream>
#include<string>
using namespace std;
int main(){
    string a,b;
    int da,db,pa=0,pb=0;
    cin>>a>>da>>b>>db;
    for(int i=0;i<a.length();i++){
        if(a[i]-'0' == da){
            pa = pa*10 + da;
        }
    }
    for(int i=0;i<b.length();i++){
        if(b[i]-'0' == db){
            pb = pb*10 + db;
        }
    }
    cout<<pa + pb;
    return 0;
}
```

### 1017 A除以B

利用人工手算除法的过程进行计算

```c++
#include<iostream>
#include<string>
using namespace std;

int main(){
    string s;
    int a,t=0,temp=0;
    cin>>s>>a;
    int len = s.length();
    t = (s[0]-'0')/a;
    if(len==1 || (t != 0 && len>1))
        cout<<t;
    temp = (s[0]-'0')%a;
    for(int i=1;i<len;i++){
        t = (10*temp + s[i]-'0')/a;
        cout<<t;
        temp = (10*temp + s[i]-'0')%a;
    }
    cout<<" "<<temp;
    return 0;
}
```

### 1019. 数字黑洞

**技巧与总结：**

- 插入0 ,利用 insert
- 排序利用 sort ，逆序则加入一个 判别式 cmp
- 利用 stoi 获得字符串开头的数字

```c++
#include <iostream>
#include <algorithm>
using namespace std;
// 用于 sort 中获得逆序的比较器
bool cmp(char a, char b) {return a > b;}
int main() {
    string s;
    cin >> s;
    // 前面插入 0
    s.insert(0, 4 - s.length(), '0');
    do{
        string a=s,b=s;
        sort(a.begin(),a.end(),cmp);
        sort(b.begin(),b.end());
        int result = stoi(a) - stoi(b);
        s = to_string(result);
        s.insert(0, 4 - s.length(), '0');
        cout<<a<<" - "<<b<<" = "<<s<<endl;
    }while(s != "6174" && s != "0000");
    return 0;
}
```

### 1020 月饼

**利用数据结构**

```c++
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
struct mooncake{
    float mount,price,unit;
};
int cmp(mooncake a,mooncake b){
    return a.unit>b.unit;
}
int main(){
    int n,need;
    cin>>n>>need;
    vector<mooncake> a(n);
    for(int i=0;i<n;i++) scanf("%f",&a[i].mount);
    for(int i=0;i<n;i++) scanf("%f",&a[i].price);
    for(int i=0;i<n;i++) a[i].unit = a[i].price/a[i].mount;
    sort(a.begin(),a.end(),cmp);
    float res = 0.0;
    for(int i=0;i<n;++i){
        if(a[i].mount<=need){
            res = res + a[i].price;
        }
        else{
            res = res + a[i].unit*need;
            break;
        }
        need -= a[i].mount;
    }
    printf("%.2f",res);
    return 0;
}
```

### 1022 D进制的A+B

```C++
#include<iostream>
using namespace std;
int main(){
    int a,b,d;
    cin>>a>>b>>d;
    int t = a+b;
    if(t==0){
        cout<<0;
        return 0;
    }
    int s[100];
    int i=0;
    while(t!=0){
        s[i++]=t%d;
        t/=d;
    }
    for(int j=i-1;j>=0;j--)
        cout<<s[j];
    return 0;
}
```



### 1021 个位数统计

```c++
#include<iostream>
#include<vector>
#include<string>

using namespace std;
int main(){
    string s;
    cin>>s;
    vector<int> a(10,0);
    for(auto &i:s){
        a[i-'0']++;
    }
    for(int i=0;i<a.size();++i){
        if(a[i]>0){
            cout<<i<<":"<<a[i]<<"\n";
        }
    }
    return 0;
}
```

### 1023 组个最小数

```c++
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
int main(){
    vector<int> input,num;
    int i=0;
    for(int m=0;m<10;m++){
        cin>>i;
        input.push_back(i);
    }
    for(int j=0;j<input.size();++j){
        for(int m=0;m<input[j];++m){
            num.push_back(j);
        }
    }
    sort(num.begin(),num.end());
    for(int b=0;b<num.size();++b){
        if(num[b]==0)
            continue;
        else {
            swap(num[0],num[b]);
            break;
        }
    }
    for(auto &v:num)
        cout<<v;
    return 0;

}
```

### 1024.  科学计数法

用`substr`

```c++
#include<iostream>
#include<string>

using namespace std;

int main(){
    string s;
    cin>>s;
    int i=0;
    while(s[i] != 'E') ++i;
    
    string t =s.substr(1,i-1);
    // 指数
    int n = stoi(s.substr(i+1));
    if(s[0]=='-') cout<<"-";

    // 指数小于零
    if(n<0){
        cout<<"0.";
        for(int j=0;j<abs(n)-1;++j) cout<<'0';
        for(int j=0;j<t.length();++j)
            if(t[j]!='.') cout<<t[j];
    }

    // 指数大于零
    else {
        cout<<t[0];
        // cnt 记录t的长度, 
        int cnt,j;
        for(j=2,cnt=0;j<t.length() && cnt<n;++j,++cnt) cout<<t[j];
        // 看是否有小数
        if(j==t.length()){
            for(int k=0;k<n-cnt;++k)
                cout<<'0';
        }
        else{
            cout<<'.';
            for(int k=j;k<t.length();++k)
                cout<<t[k];
        }
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

### 1005 Spell it Right(20 points)

Given a non-negative integer N, your task is to compute the sum of all the digits of N,and output every digit of the sum in English.

- input specification:  each input file contains one test case, each case occupies one line which contains an N(<= 10^100)
- output specification: for each case output in one line the digits of the sum in English words.There must be one spcae between two consecutive words , but no extra space at the end of a line

- sample input:  12345
- sample output:  one five

```C++
#include<string>
#include<iostream>
using namespace std;

void res_print(char s) {
	switch (s){
	case '0':cout << "zero"; break;
	case '1':cout << "one"; break;
	case '2':cout << "two"; break;
	case '3':cout << "three"; break;
	case '4':cout << "four"; break;
	case '5':cout << "five"; break;
	case '6':cout << "six"; break;
	case '7':cout << "seven"; break;
	case '8':cout << "eight"; break;
	case '9':cout << "nine"; break;
	}
}

int main() {
	string str;
	cin >> str;
	int sum = 0;
	for (auto& i : str) {
		sum += (i - '0');
	}
	auto res = to_string(sum);
	for (int i = 0; i < res.length() - 1; ++i) {
		res_print(res[i]);
		cout << " ";
	}
	res_print(res[res.length() - 1]);
	return 0;
}
```

### 1008  Elevator(20 points)

The highest building in our city has only one elevator. A request list is made up with *N* positive numbers. The numbers denote at which floors the elevator will stop, in specified order. It costs 6 seconds to move the elevator up one floor, and 4 seconds to move down one floor. The elevator will stay for 5 seconds at each stop.

For a given request list, you are to compute the total time spent to fulfill the requests on the list. The elevator is on the 0th floor at the beginning and does not have to return to the ground floor when the requests are fulfilled.

**Input Specification:**

Each input file contains one test case. Each case contains a positive integer *N*, followed by *N* positive numbers. All the numbers in the input are less than 100.

**Output Specification:**

For each test case, print the total time on a single line.

**Sample Input:**

```in
3 2 3 1
```

**Sample Output:**

```out
41
```

```c++
#include<vector>
#include<iostream>
using namespace std;

int main() {
	int input;
	vector<int> vec(0);
	while (cin >> input)
		vec.push_back(input);
	int res = vec[0] * 5;
	int N = vec[0];
	vec[0] = 0;
	for (int i = 0; i <= N-1; ++i) {
		int a = vec[i + 1] - vec[i];
		if (a > 0) { res += a * 6; }
		else if (a < 0) { res += -4 * a; }
	}
	cout << res;
	return 0;
}
```

### 1011 world cup betting  20 points

With the 2010 FIFA World Cup running, football fans the world over were becoming increasingly excited as the best players from the best teams doing battles for the World Cup trophy in South Africa. Similarly, football betting fans were putting their money where their mouths were, by laying all manner of World Cup bets.

Chinese Football Lottery provided a "Triple Winning" game. The rule of winning was simple: first select any three of the games. Then for each selected game, bet on one of the three possible results -- namely `W` for win, `T` for tie, and `L` for lose. There was an odd assigned to each result. The winner's odd would be the product of the three odds times 65%.

For example, 3 games' odds are given as the following:

```
 W    T    L
1.1  2.5  1.7
1.2  3.1  1.6
4.1  1.2  1.1
```

To obtain the maximum profit, one must buy `W` for the 3rd game, `T` for the 2nd game, and `T` for the 1st game. If each bet takes 2 yuans, then the maximum profit would be (4.1×3.1×2.5×65%−1)×2=39.31 yuans (accurate up to 2 decimal places).

**Input Specification:**

Each input file contains one test case. Each case contains the betting information of 3 games. Each game occupies a line with three distinct odds corresponding to `W`, `T` and `L`.

**Output Specification:**

For each test case, print in one line the best bet of each game, and the maximum profit accurate up to 2 decimal places. The characters and the number must be separated by one space.

**Sample Input:**

```in
1.1 2.5 1.7
1.2 3.1 1.6
4.1 1.2 1.1
```

**Sample Output:**

```out
T T W 39.31
```

```c++
#include<iostream>
using namespace std;

int main() {
	float W, T, L;
	float product = 1.0;
	for (int j = 0; j < 3; ++j) {
		while (cin >> W >> T >> L) {
			if (W >= T && W >= L) {
				cout << 'W';
				product *= W;
			}
			else if (T >= W && T >= L) {
				cout << 'T';
				product *= T;
			}
			else if (L >= W && L >= T) {
				cout << 'L';
				product *= L;
			}
			cout << " ";
		}
	}
	float res = 2 * (product * 0.65 - 1);
	printf("%.2f", res);
	return 0;
}
```

###  1015  Reversible Primes  20 points

A **reversible prime** in any number system is a prime whose "reverse" in that number system is also a prime. For example in the decimal system 73 is a reversible prime because its reverse 37 is also a prime.

Now given any two positive integers *N* (<105) and *D* (1<*D*≤10), you are supposed to tell if *N* is a reversible prime with radix *D*.

**Input Specification:**

The input file consists of several test cases. Each case occupies a line which contains two integers *N* and *D*. The input is finished by a negative *N*.

**Output Specification:**

For each test case, print in one line `Yes` if *N* is a reversible prime with radix *D*, or `No` if not.

**Sample Input:**

```in
73 10
23 2
23 10
-2
```

**Sample Output:**

```out
Yes
Yes
No
```

**解法：  对于这种输出形式 ，采用\<cstdio>中的函数.利用c语言中的scanf来逐个获取**

```c++
#include<cstdio>
#include<cmath>
using namespace std;

bool isprime(int n) {
	if (n <= 1) return false;
	int sqr = int(sqrt(n * 1.0));
	for (int i = 2; i <= sqr; ++i) {
		if (n % i == 0) {
			return false;
		}
	}
	return true;
}


/*
// 常用函数
bool isPrime(int n){
	if(n <= 1) return false;
	for(int i=2; i*i<=n; ++i){
		if(n%i == 0){
            return false;
        }
	}
    return true;
}

//  在d进制下，置逆
// 4在二进制为 100 ，二进制下置逆为 001输出为1
int reverse(int a,int d=10) {
	int res = 0;
	while (a) {
		res = res * d + a % d;
		a /= d;
	}
	return res;
}

*/


int main() {
	int n, d;
	while (scanf("%d", &n) != EOF) {
		if (n < 0) break;
		scanf("%d", &d);
		if (isprime(n) == false) {
			printf("No\n");
			continue;
		}
		int len = 0, arr[100];
		do {
			arr[len++] = n % d;
			n = n / d;
		} while (n != 0);
		for (int i = 0; i < len; ++i) {
			n = n * d + arr[i];
		}
		printf("%s", isprime(n) ? "Yes\n" : "No\n");
	}
	return 0;
}
```

### 1019  General Palindromic Number(20 point(s))

A number that will be the same when it is written forwards or backwards is known as a **Palindromic Number**. For example, 1234321 is a palindromic number. All single digit numbers are palindromic numbers.

Although palindromic numbers are most often considered in the decimal system, the concept of palindromicity can be applied to the natural numbers in any numeral system. Consider a number *N*>0 in base *b*≥2, where it is written in standard notation with *k*+1 digits *a**i* as ∑*i*=0*k*(*a**i**b**i*). Here, as usual, 0≤*a**i*<*b* for all *i* and *a**k* is non-zero. Then *N* is palindromic if and only if *a**i*=*a**k*−*i* for all *i*. Zero is written 0 in any base and is also palindromic by definition.

Given any positive decimal integer *N* and a base *b*, you are supposed to tell if *N* is a palindromic number in base *b*.

**Input Specification:**

Each input file contains one test case. Each case consists of two positive numbers *N* and *b*, where 0<*N*≤109 is the decimal number and 2≤*b*≤109 is the base. The numbers are separated by a space.

**Output Specification:**

For each test case, first print in one line `Yes` if *N* is a palindromic number in base *b*, or `No` if not. Then in the next line, print *N* as the number in base *b* in the form "*a**k* *a**k*−1 ... *a*0". Notice that there must be no extra space at the end of output.

**Sample Input 1:**

```in
27 2
```

**Sample Output 1:**

```out
Yes
1 1 0 1 1
```

**Sample Input 2:**

```in
121 5
```

**Sample Output 2:**

```out
No
4 4 1
```

```c++
#include <cstdio>
#include<iostream>
using namespace std;
int main() {
    
	int a, b;
	scanf("%d %d", &a, &b);
	int arr[40], index = 0;
	while(a != 0) {
		arr[index++] = a % b;
		a = a / b;
	}
	int flag = 0;
	for(int i = 0; i < index / 2; i++) {
		if(arr[i] != arr[index-i-1]) {
			printf("No\n");
			flag = 1;
			break;
		}
	}
	if(!flag) printf("Yes\n");
	for(int i = index - 1; i >= 0; i--) {
		printf("%d", arr[i]);
		if(i != 0) printf(" ");
	}
	if(index == 0)
		printf("0");

	return 0;
}
```

```c++
#include<iostream>
#include<vector>
using namespace std;

int reverse(int a,int d=10) {
	int res = 0;
	while (a) {
		res = res * d + a % d;
		a /= d;
	}
	return res;
}

int main(){
    int a,b;
    cin>>a>>b;
    int rev = reverse(a,b);

    if(a == rev){
        cout<<"Yes\n";
    }
    else {
        cout<<"No\n";
    }

    if(a == 0)
        cout<<0;
    else{
        vector<int> res;
        while(a){
            res.push_back(a%b);
            a /= b;
        }
        for(int i=res.size()-1;i>=1;--i){
            cout<<res[i]<<" ";
        }
        cout<<res[0];
    }
    
    return 0;
}
```



### 1023 Have Fun with Numbers (20 point(s))

Notice that the number 123456789 is a 9-digit number consisting exactly the numbers from 1 to 9, with no duplication. Double it we will obtain 246913578, which happens to be another 9-digit number consisting exactly the numbers from 1 to 9, only in a different permutation. Check to see the result if we double it again!

Now you are suppose to check if there are more numbers with this property. That is, double a given number with k digits, you are to tell if the resulting number consists of only a permutation of the digits in the original number.

Input Specification:
Each input contains one test case. Each case contains one positive integer with no more than 20 digits.

Output Specification:
For each test case, first print in a line "Yes" if doubling the input number gives a number that consists of only a permutation of the digits in the original number, or "No" if not. Then in the next line, print the doubled number.

Sample Input:
1234567899
Sample Output:
Yes
2469135798



- 利用手算乘法
- 用数组记录每个数字出现的次数
- 对比出现的次数是否相同

```c++
#include<cstdio>
#include<cstring>
using namespace std;
// 用来记录每个数出现的次数
int book[10]={0,0,0,0,0,0,0,0,0,0};
int main(){
    char num[22];
    scanf("%s",num);
    int flag = 0;
    int len = strlen(num);
    for(int i=len-1; i>=0; --i){
        int temp = num[i]-'0';
        // 在原数中出现  则 +1
        book[temp]++;
        temp = temp*2 + flag;
        flag = 0;
        if(temp>=10){
            temp =temp - 10;
            flag = 1;
        }
        // 在新数中出现  则 -1
        num[i] = (temp+'0');
        book[temp]--;
    }
    int flag1 = 0;
    // 出现次数相同则 book全是0
    for(int i=0;i<10;++i){
        if(book[i] != 0)
            flag1 = 1;
    }
	// flag == 1 即加后位数不同
    printf("%s",(flag==1||flag1==1)?"No\n":"Yes\n");
    // 打印最大的一个溢出位
    if(flag==1) printf("1");
    printf("%s",num);
    return 0;
}
```

### 1027 Colors in (Mars 20 points)

People in Mars represent the colors in their computers in a similar way as the Earth people. That is, a color is represented by a 6-digit number, where the first 2 digits are for `Red`, the middle 2 digits for `Green`, and the last 2 digits for `Blue`. The only difference is that they use radix 13 (0-9 and A-C) instead of 16. Now given a color in three decimal numbers (each between 0 and 168), you are supposed to output their Mars RGB values.

**Input Specification:**

Each input file contains one test case which occupies a line containing the three decimal color values.

**Output Specification:**

For each test case you should output the Mars RGB value in the following format: first output `#`, then followed by a 6-digit number where all the English characters must be upper-cased. If a single color is only 1-digit long, you must print a `0` to its left.

**Sample Input:**

```in
15 43 71
```

**Sample Output:**

```out
#123456
```

```c++
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
```

```c++
#include <cstdio>
using namespace std;
int main() {
    char c[14] = {"0123456789ABC"};
    printf("#");
    for(int i = 0; i < 3; i++) {
        int num;
        scanf("%d", &num);
        printf("%c%c", c[num/13], c[num%13]);
    }
    return 0;
}
```

###  1031 Hello world for U

解法：利用类似bitmap的方法来存储位置信息

先存一幅图，再将整个图打印



```c++
#include<iostream>
#include<cstring>
using namespace std;
int main(){
    char c[81],u[30][30];
    memset(u,' ',sizeof(u));
    scanf("%s",c);
    int n = strlen(c)+2;
    int n1 = n/3, n2=n/3+n%3, index=0;
    for(int i=0;i<n1;++i) u[i][0]=c[index++];
    for(int i=1;i<=n2-2;++i) u[n1-1][i] = c[index++];
    for(int i=n1-1;i>=0;--i) u[i][n2-1] = c[index++];
    for(int i=0;i<n1;++i){
        for(int j=0;j<n2;++j){
            printf("%c",u[i][j]);
        }
        printf("\n");
    }
    return 0;
}
```

###  1035   Password 20 points

```c++
#include<string>
#include<iostream>
using namespace std;
void is_correct(char& a,bool& m){
    if(a=='1'){
        a='@';
        m = false;
    }
    else if(a=='l'){
        a='L';
        m = false;
    }
    else if(a=='0'){
        a='%';
        m = false;
    }
    else if(a=='O'){
        a='o';
        m = false;
    }
}

int main(){
    int N;
    cin>>N;
    int cnt=0;
    string ID[N],PWD[N];
    for(int i=0;i<N;++i){
        bool m=true;
        string id,pwd;
        cin>>id>>pwd;
        for(auto &c:pwd){
            is_correct(c,m);
        }
        if(!m){
            ID[cnt] = id;
            PWD[cnt++] = pwd;
        }
    }
    if(cnt == 0){
        if(N==1)
            printf("There is %d account and no account is modified",N);
        else 
            printf("There are %d accounts and no account is modified",N);
    }
    else {
        cout<<cnt<<"\n";
        for(int i=0;i<cnt;++i){
            cout<<ID[i]<<' '<<PWD[i];
            if(i!=cnt-1) cout<<'\n';
        }
    }
    return 0;
}
```

### 1041 Be Unique

```c++
#include<cstdio>
using namespace std;
int a[100001],m[100000];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%d",&a[i]);
        m[a[i]]++;
    }
    for(int i=0;i<n;++i){
        if(m[a[i]] == 1){
            printf("%d",a[i]);
            return 0;
        }
    }
    printf("None");
    return 0;
}
```



### 1046   Shortest Distance(  20point(s) )

The task is really simple: given *N* exits on a highway which forms a simple cycle, you are supposed to tell the shortest distance between any pair of exits.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains an integer *N* (in [3,105]), followed by *N* integer distances *D*1 *D*2 ⋯ *D**N*, where *D**i* is the distance between the *i*-th and the (*i*+1)-st exits, and *D**N* is between the *N*-th and the 1st exits. All the numbers in a line are separated by a space. The second line gives a positive integer *M* (≤104), with *M* lines follow, each contains a pair of exit numbers, provided that the exits are numbered from 1 to *N*. It is guaranteed that the total round trip distance is no more than 107.

**Output Specification:**

For each test case, print your results in *M* lines, each contains the shortest distance between the corresponding given pair of exits.

**Sample Input:**

```in
5 1 2 4 14 9
3
1 3
2 5
4 1
```

**Sample Output:**

```out
3
10
7
```

```c++


#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

//  解法： 时间复杂度O(N)
int main(){
    int N;
    cin>>N;
    vector<int> D;
    int num;
    cin>>num;
    D.push_back(num);
    for(int i=1;i<N;++i){
        cin>>num;
        D.push_back(num+D[i-1]);
    }

    int M;
    cin>>M;

    for(int i=0;i<M;++i){
        int a,b;
        cin>>a>>b;
        int max_num = max(a,b);
        int min_num = min(a,b);
        int dis_A = D[max_num-2]-D[min_num-2];
        cout<<min(dis_A, D[N-1]-dis_A);
        if(i!=M-1) cout<<'\n';
    }


    return 0;
}

// 下面解法时间复杂度O(n^2)   超时

/* 
int main(){
    int N;
    cin>>N;
    vector<int> D;
    for(int i=0;i<N;++i){
        int n;
        cin>>n;
        D.push_back(n);
    }
       
    int M;
    cin>>M;
    int sum=0;
    for(auto &i:D){
        sum += i;
    }

    for(int i=0;i<M;++i){
        int a,b;
        cin>>a>>b;
        if(a == b) cout<<0;
        else{
        int ma = max(a,b);
        int mi = min(a,b);
        int sum_1 = 0;
        for(int i=mi-1;i<=ma-2;++i)
            sum_1 += D[i];
        cout<<min(sum_1,sum-sum_1);
        }
        if(i!=M-1) cout<<'\n';
    }
    return 0;
}
*/
```

###  1050  String Subtraction (20 point(s))

Given two strings *S*1 and *S*2, *S*=*S*1−*S*2 is defined to be the remaining string after taking all the characters in *S*2 from *S*1. Your task is simply to calculate *S*1−*S*2 for any given strings. However, it might not be that simple to do it **fast**.

**Input Specification:**

Each input file contains one test case. Each case consists of two lines which gives *S*1 and *S*2, respectively. The string lengths of both strings are no more than 104. It is guaranteed that all the characters are visible ASCII codes and white space, and a new line character signals the end of a string.

**Output Specification:**

For each test case, print *S*1−*S*2 in one line.

**Sample Input:**

```in
They are students.
aeiou
```

**Sample Output:**

```out
Thy r stdnts.
```



**解法一：暴力**

时间复杂度 O(N*M)

空间复杂度 O(1)

```c++
#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
    string s1,s2;
    getline(cin,s1);
    getline(cin,s2);

    for(auto &i:s1){
        if(s2.end() == find(s2.begin(),s2.end(),i)){
            cout<<i;
        }
    }
    return 0;
}
```

**解法二：hash set**

时间复杂度 O(n)

空间复杂度 O(n)

```c++
#include<unordered_set>
#include<string>
#include<iostream>

using namespace std;

int main(){
    string s1,s2;
    getline(cin,s1);
    getline(cin,s2);
    unordered_set<char> set;
    for(auto &i:s2){
        set.insert(i);
    }
    for(auto &i:s1){
        if(set.count(i) == 0){
            cout<<i;
        }
    }
    return 0;
}
```

### 1054 The Dominant Color (20 point(s))

Behind the scenes in the computer's memory, color is always talked about as a series of 24 bits of information for each pixel. In an image, the color with the largest proportional area is called the dominant color. A **strictly** dominant color takes more than half of the total area. Now given an image of resolution *M* by *N* (for example, 800×600), you are supposed to point out the strictly dominant color.

**Input Specification:**

Each input file contains one test case. For each case, the first line contains 2 positive numbers: *M* (≤800) and *N* (≤600) which are the resolutions of the image. Then *N* lines follow, each contains *M* digital colors in the range [0,224). It is guaranteed that the strictly dominant color exists for each input image. All the numbers in a line are separated by a space.

**Output Specification:**

For each test case, simply print the dominant color in a line.

**Sample Input:**

```in
5 3
0 0 255 16777215 24
24 24 0 0 24
24 0 24 24 24
```

**Sample Output:**

```out
24
```

**解法一：排序利用sort**

```c++
#include<iostream>
#include<vector>
#include<algorithm>
using namespace  std;
int main(){
    int M,N;
    cin>>M>>N;
    vector<int> res;
    for(int i=0;i<M;++i){
        for(int j=0;j<N;++j){
            int num;
            cin>>num;
            res.push_back(num);
        }
    }
    sort(res.begin(),res.end());
    cout<<res[res.size()/2];
    return 0;
}
```

**解法二: 利用 map记录每个元素出现的次数**

空间换时间

```c++
#include <iostream>
#include <map>
using namespace std;
int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    map<int, int> arr;
    int half = m * n / 2;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int temp;
            scanf("%d", &temp);
            arr[temp]++;
            if(arr[temp] > half) {
                printf("%d", temp);
                return 0;
            }
        }
    }
    return 0;
}
```

### 1058. A+B in Hogwarts (20 point(s))

If you are a fan of Harry Potter, you would know the world of magic has its own currency system -- as Hagrid explained it to Harry, "Seventeen silver Sickles to a Galleon and twenty-nine Knuts to a Sickle, it's easy enough." Your job is to write a program to compute *A*+*B* where *A* and *B* are given in the standard form of `Galleon.Sickle.Knut` (`Galleon` is an integer in [0,107], `Sickle` is an integer in [0, 17), and `Knut` is an integer in [0, 29)).

**Input Specification:**

Each input file contains one test case which occupies a line with *A* and *B* in the standard form, separated by one space.

**Output Specification:**

For each test case you should output the sum of *A* and *B* in one line, with the same format as the input.

**Sample Input:**

```in
3.2.1 10.16.27
```

**Sample Output:**

```out
14.1.28
```

```c++
#include<iostream>
#include<cstdio>
using namespace std;
int main(){
    long long  a,b,c,d,e,f;
    scanf("%lld.%lld.%lld %lld.%lld.%lld",&a,&b,&c,&d,&e,&f);
    long long flag = 0,cnt1=0,cnt2=0,cnt3=0;
    cnt1 = (c+f)%29;
    flag = (c+f)/29;

    cnt2 = (b+e+flag)%17;
    flag = (b+e+flag)/17;
    
    cnt3 = flag + a + d;
    cout<<cnt3<<"."<<cnt2<<"."<<cnt1;
    return 0;
}
```

### 1065 A+B and C (64bit)  20 points

Given three integers *A*, *B* and *C* in [−263,263], you are supposed to tell whether *A*+*B*>*C*.

**Input Specification:**

The first line of the input gives the positive number of test cases, *T* (≤10). Then *T* test cases follow, each consists of a single line containing three integers *A*, *B* and *C*, separated by single spaces.

**Output Specification:**

For each test case, output in one line `Case #X: true` if *A*+*B*>*C*, or `Case #X: false` otherwise, where *X* is the case number (starting from 1).

**Sample Input:**

```in
3
1 2 3
2 3 4
9223372036854775807 -9223372036854775808 0
```

**Sample Output:**

```out
Case #1: false
Case #2: true
Case #3: false
```

**解法：** 由两个数之和来判断溢出情况

```c++
#include<cstdio>
using namespace std;
int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        long long a,b,c;
        scanf("%lld %lld %lld",&a,&b,&c);
        long long sum = a+b;
        // 溢出
        if(a>0 && b>0 && sum< 0){
            printf("Case #%d: true\n",i+1);
        }
        else if(a<0 && b<0 && sum>= 0){
            printf("Case #%d: fasle\n",i+1);
        }
        else if(sum > c){
            printf("Case #%d: true\n",i+1);
        }
        else {
            printf("Case #%d: false\n",i+1);
        }
    }
    return 0;
}
```



###   1073 Scientific Notation(20point(s))


Scientific notation is the way that scientists easily handle very large numbers or very small numbers. The notation matches the regular expression [+-][1-9]`.`[0-9]+E[+-][0-9]+ which means that the integer portion has exactly one digit, there is at least one digit in the fractional portion, and the number and its exponent's signs are always provided even when they are positive.

Now given a real number *A* in scientific notation, you are supposed to print *A* in the conventional notation while keeping all the significant figures.

**Input Specification:**

Each input contains one test case. For each case, there is one line containing the real number *A* in scientific notation. The number is no more than 9999 bytes in length and the exponent's absolute value is no more than 9999.

**Output Specification:**

For each test case, print in one line the input number *A* in the conventional notation, with all the significant figures kept, including trailing zeros.

**Sample Input 1:**

```in
+1.23400E-03
```

**Sample Output 1:**

```out
0.00123400
```

**Sample Input 2:**

```in
-1.2E+10
```

**Sample Output 2:**

```out
-12000000000
```

- `std::string`的范围  `[begin,end)`


```c++
#include<iostream>
#include<string>
#include<algorithm>
using namespace std;
int main(){
    string str;
    cin>>str;
    if(str[0]=='-') cout<<'-';
    // 找到小数点位置
    auto ptr_1 = find(str.begin(),str.end(),'.');
    // 找到E的位置
    auto ptr_E = find(str.begin(),str.end(),'E');
    // 判断是否是小数
    bool exp = *(ptr_E+1)=='+'?true:false;
    // 获取每部分数值
    // 指数
    int exp_num = stoi(string(ptr_E+2,str.end()));
    auto exp_num_str = to_string(exp_num);
    // 头部
    int head = str[1]-'0';
    auto head_str = to_string(head);
	// 中间   
    auto body = string(ptr_1+1,ptr_E);
    int len = body.length();
	// 是小数
    if(!exp){
        cout<<"0.";
        for(int i=1;i<=exp_num-1;++i)
            cout<<'0';
        cout<<str[1]<<body;
    }
    else{
        cout<<str[1];
        // 指数较大
        if(exp_num>len){
            cout<<body;
            for(int i=1;i<=exp_num-len;++i)
                cout<<'0';
        }
        else if(exp_num == len){
            cout<<body;
        }
        else{
            for(int i=0;i<len;++i){
                cout<<body[i];
                if(i+1 ==exp_num)
                    cout<<'.';
            }
        }
    }
    return 0;
}
```

