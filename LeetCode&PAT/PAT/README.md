

# PAT

[TOC]

## 常用函数实现

```c++
// 判断是否时质数
bool isPrime(int n){
	if(n <= 1) return false;
	for(int i=2; i*i<=n; ++i){
		if(n%i == 0){
            return false;
        }
	}
    return true;
}

//  在d进制下，置逆  123(10) --->   321(10)
int reverse(int a,int d=10) {
	int res = 0;
	while (a) {
		res = res * d + a % d;
		a /= d;
	}
	return res;
}
```



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



