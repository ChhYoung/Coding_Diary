/*
 * @lc app=leetcode id=234 lang=cpp
 *
 * [234] Palindrome Linked List
 */
#include<iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
private:
    ListNode* reverse(ListNode* head){
        if(head==nullptr || head->next==nullptr)
            return head;
        // 三个指针分别指向 前 ，当前，后
        ListNode* pre = head;
        ListNode* cur = head->next;
        ListNode* next = cur->next;
        // 将头节点置为尾节点
        head->next = nullptr;
        while(true){
            cur->next = pre;
            pre = cur;
            cur = next;
            if(cur == nullptr)
                break;
            next = cur->next;
        }
        return pre;
    }    

public:
    bool isPalindrome(ListNode* head) {
        if(head == nullptr || head->next == nullptr)
            return true;
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast->next!=nullptr && fast->next->next!=nullptr){
            slow = slow->next;
            fast = fast->next->next;
        }
        // 将slow后的元素置逆
        slow->next = reverse(slow->next);
        slow = slow->next;
        ListNode* cur = head;
        while(slow != nullptr){
            if(cur->val != slow->val)
                return false;
            else{
                slow = slow->next;
                cur = cur->next;
            }
        }
        return true;
    }
};

