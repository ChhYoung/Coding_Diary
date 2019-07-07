/*
 * @lc app=leetcode id=141 lang=cpp
 *
 * [141] Linked List Cycle
 */

  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(nullptr) {}
  };
/* 
// solution 1 : two pointer
class Solution {
public:
    bool hasCycle(ListNode *head) {
        auto fast = head;
        auto slow  = head;
        while(true){
            if(!fast || !slow || !(fast->next) || !(fast->next->next)){
                return false;
            }
            else{
                fast = fast->next->next;
                slow = slow->next;
                if(fast == slow){
                    return true;
                }
            }
        }
    }
};
*/ 

// solution 2: hash table

#include<set>

class Solution {
public:
    bool hasCycle(ListNode *head) {
        std::set<ListNode*> res;
        auto ptr = head;
        while(true){
            if(!ptr ) return false;
            else if(res.find(ptr) == res.end()){
                res.insert(ptr);
                ptr = ptr->next;
            }
            else if(res.find(ptr) != res.end()){
                return true;
            }       
        }
    }
};
