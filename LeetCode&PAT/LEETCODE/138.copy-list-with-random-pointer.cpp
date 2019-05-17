/*
 * @lc app=leetcode id=138 lang=cpp
 *
 * [138] Copy List with Random Pointer
 *
 * https://leetcode.com/problems/copy-list-with-random-pointer/description/
 *
 * algorithms
 * Medium (26.47%)
 * Total Accepted:    237.1K
 * Total Submissions: 893K
 * Testcase Example:  '{"$id":"1","next":{"$id":"2","next":null,"random":{"$ref":"2"},"val":2},"random":{"$ref":"2"},"val":1}'
 *
 * A linked list is given such that each node contains an additional random
 * pointer which could point to any node in the list or null.
 * 
 * Return a deep copy of the list.
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * 
 * 
 * Input:
 * 
 * {"$id":"1","next":{"$id":"2","next":null,"random":{"$ref":"2"},"val":2},"random":{"$ref":"2"},"val":1}
 * 
 * Explanation:
 * Node 1's value is 1, both of its next and random pointer points to Node 2.
 * Node 2's value is 2, its next pointer points to null and its random pointer
 * points to itself.
 * 
 * 
 * 
 * 
 * Note:
 * 
 * 
 * You must return the copy of the given head as a reference to the cloned
 * list.
 * 
 * 
 */
/*
// Definition for a Node.*/

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

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(!head) 
            return head;
        Node* p = head;
        //生成新节点并修改next
        while(p){
            Node* pNode = new Node(p->val);
            pNode->next = p->next;
            p->next = pNode;
            p = pNode->next;
        }
        //修改random
        p = head;
        while(p){
            if(p->random)
                p->next->random = p->random->next;
            else
                p->next->random = nullptr;
            p = p->next->next;
        }
        //分离，返回Clone->head
        p = head;
        Node* pHead = head->next;
        Node* pClone = head->next;
        while(p->next){
            p->next = pClone->next;
            p = pClone;
            pClone = p->next;
        }
        return pHead;
    }
};

