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

#### 14.LCP
