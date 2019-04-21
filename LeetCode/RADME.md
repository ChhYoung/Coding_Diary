#leetcode

####138.Copy List with Random Pointer
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
