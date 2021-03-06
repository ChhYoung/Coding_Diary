# leetcode

#### 1. Two Sum

> Given an array of integers, return **indices** of the two numbers such that they add up to a specific target.
>
> You may assume that each input would have **exactly** one solution, and you may not use the *same* element twice.
>
> **example**:
>
> ```
> Given nums = [2, 7, 11, 15], target = 9,
> Because nums[0] + nums[1] = 2 + 7 = 9,
> return [0, 1].
> ```

1. 暴力解法：
时间复杂度O(n^2)  
空间复杂度O(1)
```c++
class Solution{
public:
    vector<int> twoSum(vector<int>& num, int target){
        for(int i = 0;i < nums.size(); ++i){
            for(int j = i+1;j < nums.size(); ++j){
                if(nums[i] + nums[j] == target)
                return [i,j];
            }
        }
        throw invalid_argument("the input has no solution");
    }
};
```
2. hash 用一个hash表，存储每个数对应的下标,复杂度O(N)
```c++
class Solution{
public:
    vector<int> twoSum(vector<int>& num, int target){
        unordered_map<int,int> mapping;
        vector<int> result;
        for(int i=0;i<num.size();++i){
            mapping[num[i]] = i;
        }
        for(int i=0;i<num.size();++i){
            const int gap = target - num[i];
            if(mapping.find(gap) != mapping.end() && mapping[gap] > i){
                result.push_back(i);
                result.push_back(mapping[gap]);
                break;
            }
        }
        return result;
    }
};
```
#### 2. add two sum
You are given two non-empty linked lists representing two non-negative integers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

- example
Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
Explanation: 342 + 465 = 807.

1. 普通方法建立一个新链表，这个解法的关键在于链表边界的判断与确定，结果超过10后，如何来确定carrier
时间复杂度 O(n)
空间复杂度 O(n)

```c++
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        ListNode *p1 = l1, *p2 = l2;
        ListNode *dummyHead = new ListNode(-1);
        ListNode *cur = dummyHead;
        int carrier = 0;
        while(p1 || p2){
            // 边界确定
            int a = p1 ? p1->val : 0;
            int b = p2 ? p2->val : 0;
            cur->next = new ListNode((a + b + carrier) % 10);
            carrier = (a + b + carrier)/10;

            // 边界确定
            cur = cur->next;
            p1 = p1 ? p1->next : NULL;
            p2 = p2 ? p2->next : NULL;
        }

        // 边界确定
        cur->next = carrier ? new ListNode(1) : NULL;
        ListNode* ret = dummyHead->next;
        delete dummyHead;
        return ret;
    }
};
```
2. using l1 as the result list
时间复杂度 O(n)
空间复杂度 O(n)
```c++
class Solution{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        ListNode *p1 = l1;
        ListNode *p2 = l2;
        ListNode *pre = NULL;
        int carrier = 0;
        while(p1 || p2){
            int a = p1 ? p1->val : 0;
            int b = p2 ? p2->val : 0;
            if(p1)
                p1->val = (a + b + carrier) % 10;
            else{
                pre->next = new ListNode((a + b + carrier) % 10);
                p1 = pre;
            }
            carrier = (a + b + carrier) / 10;
            pre = p1;
            p1 = p1->next;
            if(p2)
                p2 = p2->next;
        }
        pre->next = carrier ? new ListNode(1) : NULL;
        return l1;
    }
};
```
3. 用最长的list来保存结果
时间复杂度 O(n)
空间复杂度 O(1)
```c++
class Solution{
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2){
        int len1 = getLen(l1),len2 = getLen(l2);
        // 一个指向长的，一个指向短的
        ListNode *p1 = len1 > len2 ? l1 : l2;
        ListNode *p2 = len2 > len1 ? l1 : l2;

        ListNode* pre =NULL;
        int carrier = 0;
        while(p1){
            int a = p1->val;
            int b = p2 ? p2->val : 0;
            p1->val = (a + b + carrier) % 10;
            carrier = (a + b + carrier) / 10;

            pre = p1;
            p1 = p1->next;
            p2 = p2 ? p2->next : NULL;
        }
        pre->next = carrier ? new ListNode(1) : NULL;
        return len1 > len2 ? l1 : l2;
    }

private:
    int getLen(ListNode* l){
        int res = 0;
        while(l){
            ++res;
            l = l->next;
        }
        return res;
    }
};
```

#### 342.Power of Four

Given an integer (signed 32 bits), write a function to check whether it is a power of 4.

1. 暴力解法: 

   - runtime : 4ms, faster than 99.37%

   - memory usage : 8.2MB,  less than 11.97%

   ```c++
   class Solution {
   public:
       bool isPowerOfFour(int num) {
          
           while(num != 0 && num%4 == 0){
               num /= 4;
           }
           if (num == 1)
               return true;
           else 
               return false;    
       }
   };
   ```

2. 利用二进制规律

在二进制中4的幂次方中1都在奇数位。

* 首先判断是否是2的次幂
* 再与 0x55555555相与，如果得到的结果是本身则是4的次幂

- runtime : 4ms, faster than 99.37%
- memory usage : 8.1 MB,  less than 28.87%

```c++
    bool isPowerOfFour(int num) {
		return num > 0 && !(num & (num - 1)) && (num & 0x55555555) == num;   
    }
```

#### 3. Longest subtring without repeating characters

> Given a string, find the length of the **longest substring**  without repeating  character

exmaple 1 : 

- input : "abcabcabb"
- ouput: 3
- the answer is "abc" ，with the length of 3

exmaple 2 :

- input : "bbbbb"
- output : 1 
- the answer is "b", with the length of 1

exmaple 3:

- input : "pwwkew"
- output : 3
- the answer is "wke",with the length of 3

**分析:**利用贪心算法，从左向右扫描，遇到重复字母，用以上重复字母的index+1为新的扫描起点，重新开始扫描，直到最后一个字母。(注意最大长度与搜索开始位置)

- 时间复杂度O(n)
- 空间复杂度O(1)

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
		const int ASCII_MAX = 255;
        int last[ASCII_MAX]; // 用来记录字符所在位置   'a' == 97
        int start = 0; // 开始位置
        // 初始化 last
        fill(last, last + ASCII_MAX,-1);
        int max_len = 0;
        for(int i = 0; i < s.size(); ++i){
            // 本来应该是-1，如果出现重复则last对应的要比start大
            // 找到一个重复，置开始位,得长度
            // 注意这个loop中只解决有重复出现得最大长度，当无重复时还没有更新
            if(last[s[i]] >= start){
                max_len = max(i - start,max_len);
                start = last[s[i]] + 1;
            }
            // 置last中对应字符数为其在s中的 当前的 index
            last[s[i]] = i;
        }
        // 对于无重复的最后一次，  如"abcd"
        return max((int)s.size()-start, max_len);
    }
};

```

#### 4. Median of Two Sorted Arrays

There are two sorted arrays **nums1** and **nums2** of size m and n respectively.

Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

You may assume **nums1** and **nums2** cannot be both empty.

> example 1 : 
>
> nums1 = [1,3]
>
> nums2 = [2]
>
> the median is 2.0

>example 2 :
>
>nums1 = [1,2]
>
>nums2 = [3,4]
>
>the median is 2.5

- 思路一：时间复杂度O(m+n)

  找到第  k 大的数

  一个计数器 c ，记当前已经找到第 c 大的数

  用 merge sort 一个指针pA指向A，一个pB指向B，A的小则++ pA, B的小则++ pB,  同时 ++c，当c == k

  即为要找的数，时间复杂度 O(k) ,当k接近 m + n 时接近 O( m + n )

  这里相当于每次删除 一个一定小于K的元素

  每次删除一半，类似二分查找，充分利用有效性

- 思路二：时间复杂度O(log(m+n))

  > 先从第k大的元素开始入手，**假设A和B的元素个数都大于k/2**，将A的第k/2个元素`A[k/2-1]`与B的第k/2个元素`B[k/2-1]`相比较，如果**A[k/2 - 1] < B[k/2 - 1] **,则说明`A[0]--A[k/2-1]`一定在AB整体的前k个元素内部，则可以删除`A[0]--A[k/2-1]`, 同理**A[k/2 - 1] > B[k/2 - 1]**则删除`B[0]--B[k/2-1]`

  - `A[k/2 - 1] < B[k/2 - 1]` 删除`A[0]--A[k/2-1]`
  - `A[k/2 - 1] > B[k/2 - 1]`删除`B[0]--B[k/2-1]`
  - `A[k/2 - 1] = B[k/2 - 1]`则找到第k大的元素

  > **若有一个小于长度k/2,**则 假设A的长度最小，比较A[m-1] 与 B[k - m - 1]的大小

  - A[m - 1]  <  B[k - m - 1]， 即一个长度要为0的情况，则可以直接得到结果
  - A[m - 1]  >  B[k - m - 1],    删除`B[0]--B[k - m - 1]`
  - A[m - 1]  >  B[k - m - 1],    则找到第k大的元素

  **实现细节**

```c++
class Solution {
public:
    double findMedianSortedArrays(vector<int>& A, vector<int>& B) {
        const int m = A.size();
        const int n = B.size();
        int total = m + n;
        // 判断总长度是奇数还是偶数
        if (total & 0x1)
            // 总长为奇数则直接找第  int((m+n)/2) + 1  大的数
            return find_kth(A.begin() , m , B.begin() , n , total/2 + 1);
        else 
            // 总长为偶数则找 第 int((m+n)/2) 和 第 int((m+n)/2) + 1 大的数
            return (find_kth(A.begin() , m , B.begin() , n , total/2)
                  + find_kth(A.begin() , m , B.begin() , n , total/2 + 1))/ 2.0;
    }

private:
    static int find_kth(std::vector<int>::const_iterator A, int m,
                        std::vector<int>::const_iterator B, int n, int k){
        // 始终令 m <= n
        if (m > n) return find_kth(B, n, A, m,k);
        if ( m == 0 ) return  *(B + k - 1);
        if ( k == 1) return min(*A,*B);
        
        // 将k划为两部分
        // 考虑一个小于k/2的情况,则令一个为本身长度(不划分)
        int ia = min(k / 2, m), ib = k - ia;
        // A[k/2 - 1] < B[k/2 - 1]
        if ( *(A + ia -1) < *(B + ib -1))
            // 更新长度 找第 看 k-ia 大小的
            return find_kth(A + ia , m - ia, B, n,k - ia);
        else if ( *(A + ia -1) > *(B + ib -1))
            return find_kth(A , m , B + ib , n - ib,k - ib);
        else 
            return A[ia - 1];
    }
};
```

#### 7. Longest Palindromic Substring

Given a string S, find the longest palindromic substring in S. You may assume that the maximum length
of S is 1000, and there exists one unique longest palindromic substring.

解法：

- 备忘录法，复杂度O(n^2) ，用f[i][j]表示[i,j]间最长的回文子串
- 动态规划,
![](pics/_tongtaioguihua.png)
- Manacher，

```c++
// 动态规划
class Solution{
public:
    string longestPalindrome(const string& s){
     	const int n = s.size();
        // 状态表
        bool f[n][n];
        fill_n(&f[0][0], n*n, false);
        
        // 最大回文串的长度，起点
        size_t max_len = 1, start = 0;
        
        for(size_t i = 0; i < s.size();++i){
            // i == j
            // 设置 f[i][i] 为 true
    	    f[i][i] = true;
            for(size_t j = 0; j < i; j++){
                // 
                f[j][i] = (s[j] == s[i] && (i - j < 2 || f[j+1][i-1]));
                if( f[j][i] && max_len < (i - j + 1)){
                    max_len = i - j + 1;
                    start = j;
                }
            }
        }
        return s.substr(start,max_len);
    }
};

```



#### 138.Copy List with Random Pointer

>A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null.
Return a deep copy of the list.

思路: 
1.先在原来两个顺序节点中间插入一个前一个的复制节点，
        如A->B   变为   A->A*->B->B*
      2.修改random
      3.分离
      时间复杂度O(n),空间复杂度O(1)
```cpp

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node() {}

    Node(int _val, Node* _next, Node* _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};
// solution

class Solution{
public:
    Node* copyRandomList(Node* head) {
            if(!head) 
                return head;
        Node* p = head;

        // 1.创建并插入
        while(p){
            Node* pNode = new Node(p->val);
            pNode->next = p->next;
            p->next = pNode;
            p = pNode->next;
        }

        // 2.修改random
        p = head;
        while(p){
            if(p->random)
                p->next->random = p->random;
            else 
                p->next->random = nullptr;
            p = p->next->next;
        }

        // 3.断开并返回拷贝
        p = head;
        Node* clone = head->next;
        Node* pClone = head->next;//clone node 的指针
        while(p->next){
            p->next = pClone->next;
            pClone = p->next;
        }
        reuturn clone;
    }
};
```
#### 7. reverse integer

> given a 32 bit signed integer , reverse digits of an integer.

**重点在于 overflow**

解法一： using long type ,注意INT_MAX 和INT_MIN

```c++
class Solution{
public:
    int reverse(int x){
        long result = 0;
        while(x != 0){
            result = result * 10 + x % 10;
            x /= 10;
        }
        return (result > INT_MAX || result < INT_MIN) ？ 0 ： resul;
    }
};
```



#### 24.Swap Nodes in Pairs

> Given a linked list, swap every two adjacent nodes and return its head.
You may not modify the values in the list's nodes, only nodes itself may be changed.
> Given 1->2->3->4, you should return the list as 2->1->4->3.

1.利用递归：从尾部开始每两个元素换位置；

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(!head || !head->next) return head;
        ListNode *next = head->next;
        ListNode *n = swapPairs(head->next->next);
        next->next = head;
        head->next = n;
        return next;
    }        
};
```
2.直接遍历

```c++
class Solution{
public:
    ListNode* swapPairs(ListNode* head) {
		ListNode * dummyHead = new ListNode(0);
        dummyHead->next = head;
        ListNode* p = dummyHead;
        while(p->next && p->next->next){
            ListNode* node1 = p->next;
            ListNode* node2 = node1->next;
            ListNode* next  = node2->next;
            node2->next = node1;
            node1->next = next;
            p->next = node2;
            p = node1;
        }
        ListNode* retHead = dummyHead->next;
        delete dummyHead;
        return retHead;
    }        
};
```



#### 67.Add Binary

>Given two binary strings, return their sum (also a binary string).
The input strings are both non-empty and contains only characters 1 or 0.
>Input: a = "11", b = "1"
Output: "100"

```cpp
class Solution{
public:
    string addBinary(string a,string b){
        string res = a.size() > b.size() ? a : b;
        string add = a.size() < b.size() ? a : b;
        int index = res.size() - 1;
        for(int i = add.size() - 1; i >= 0 ;i--){
            res[index] += add[i] - '0';
            index--;
        }

        for(int i = res.size() - 1; i > 0; i--)
            if(res[i] > '1'){
                res[i-1]++;
                res[i] = '0' + (res[i]-'0')%2;
            }

        if(res[0]>'1'){
            res[0] = '0' + (res[0]-'0')%2;
            res = '1'+res;}
        return res;
    }
}
```
#### 28.Implement strStr()
>Implement strStr().
Return the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack.
Example 1:
Input: haystack = "hello", needle = "ll"
Output: 2
Example 2:
Input: haystack = "aaaaa", needle = "bba"
Output: -1

1. 暴力遍历 时间复杂度O(nm)
```cpp
class Solution{
public:
    int strStr(string haystack, string needle){
        int n = haystack.size(),m = needle.size();
        for(int i = 0;i < n-m;i++){
            int j=0;
            for(j=0;j < m ;j++)
                if(haystack[i+j] != needl[j])
                    break;
            if(j == m)
                return i;
        }
        return i;
    }
}
```

#### 53. Maximum Subarray

> Given an integer array `nums`, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.

example:

Input  : [-2,1,-3,4,-1,2,1,-5,4]

Output: 6

[4,-1,2,1] has the max sum

**解决：**

**1.利用动态规划**

> 在遍历整个数组时对于每个元素，它有两种选择，
>
> 1. 加入之前的subarray，2.  自己建一个新的subarray
>
> 在动态规划中：
>
> 1. 若之前的subarray总体的和小于等于0，则认为 它对后面的sub和 没有贡献
>
>    sum + nums[j]  <= nums[j]
>
> 2. 若大于0，则认为它对后面的sub和有贡献,即以当前nums[j]结尾的subarray的sum，
>
>    sum + nums[j]  > nums[j]
>
> 设当前状态f[j] 表示以nums[j]结尾的subarray的和，则f[j]的状态转移方程为
>
> f[j] =  max( f[j-1]+nums[j]  ,  nums[j] )
>
> res = max{ f[i] }   0<=i<=n-1
>
> **利用f[j]来记录前面的subarray和**
>
> **利用res来记录最大的f[j]**



时间复杂度：O（n）

- runtime : 4ms    faster than 99.79%
- memory uage : 9.4MB   less than 59.66%

```c++
class Solution{
public:
    int maxSubArray(vector<int>& nums) {
        int res = MIN_INT， f = 0;
        for(int i = 0; i<nums.size();++i){
            f = max(f+nums[i],nums[i]);
            res = max(res,f);
        }
        return res;
    }
};
```

**2. 处理后后枚举，连续子序列的和 为两个前缀和的差值，找到最大和最小的前缀和，求差值**

时间复杂度: O(n)

- runtime : 4ms   faster than 99.79%
- memory usage: 9.6MB   less than 53.95%

```c++
class Solution{
public:
    int maxSubArray(vector<int>& nums){
        return mcss(nums.begin(),nums.end());
    }
private:
    template<typename Iter>
    static int mcss(Iter begin,Iter end){
        int result,cur_min;
        const int n = distance(begin,end);
        int *sum = new int[n+1]; //求前n项和
        
        sum[0] = 0;
        result = INT_MIN;
        cur_min = sum[0];
        for(int i = 1;i<=n;++i){
            sum[i] = sum[i-1] + *(begin+i-1);
        }
        for(int i = 0;i<=n;++i){
            res = max(res , sum[i]-cur_min);
            cur_min = min(cur_min,sum[i]);
        }
        delete[] sum;
        return res;
    }
};

```

#### 70.Climbing Stairs

You are climbing a stair case. It takes *n* steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

**Note:** Given *n* will be a positive integer.

**example 1 :**

input: 2

output: 2

```
1. 1 step + 1 step
2. 2 steps
```

**example 2 :**

input: 3

output: 3
```
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
```

**方法1：递归**

**当数字较大是会超时,不行**

```c++
class Solution{
public:
    int climbStairs(int n){
        if(n <= 0)
            return 0;
        else if(n == 1)
            return 1;
        else if(n == 2)
            return 2;
        return climbStairs(n-2)+climbStairs(n-1);
    }    
};
```

**注意到这是一个fib数列，可以利用迭代求fib数列和的方法，或者利用fib数列求和公式来求解**

**方法二：迭代求fib数列和**

时间复杂度O(n)

空间复杂度O(1)

runtime:  4ms  faster than 89.77%

memory usage : 8.4 MB    less than 55.73%

```c++
class Solution{
public:
    int climbStairs(int n){
		int prev = 0;
        int cur = 1;
        for(int i = 1; i<= n;++i){
            int tmp = cur;
            cur += prev;
            prev = tmp;
        }
        return cur;
    }    
};
```

**方法三：**利用fib求和公式

时间复杂度O(1)

空间复杂度O(1)

```c++
class Solution{
public:
    int climbStairs(int n){
		const double s = sqrt(5);
        return floor( (pow((1+s)/2,n+1) + pow((1-s)/2,n+1))/s+0.5);
    }    
};
```

