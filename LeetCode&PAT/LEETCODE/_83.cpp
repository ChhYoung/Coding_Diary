/**
 * Definition for singly-linked list.*/
#include<iostream>
#include<array>
//#include"/home/yangchonghuan/Desktop/Code_D/Coding_Diary/C++Project/C++内存泄露检测器/LeakDetector.h"
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        for(ListNode* p=head;p&&p->next;){
            if(p->val==p->next->val){
                auto temp=p->next;
                p->next=temp->next;
                // 不删除版本会有内存泄露的问题
                delete temp;
                continue;
            }
            p=p->next;
        }
        return head;
    }
};

template<typename T>
ListNode* GenListNOde(T a){
    ListNode* head = new ListNode(0);
    auto ptr = head;
    for(int i=0;i<a.size();i++){
        ptr->next = new ListNode(a[i]);
        ptr = ptr->next;
    }
    return head->next;
}

void display(ListNode* k){
    std::cout<<"the array:\n";
    while(k){
        std::cout<<k->val<<",";
        k = k->next;
    }
    std::cout<<"\n";
}

int main(){
    /* 
    int test_1[] = {1,1,1};
    int test_2[] = {1,1,1,2,2,2};
    int test_3[] = {1,1,1,2,2,3};
    int test_4[] = {1,1,1,2,3,3,5};*/
    std::array<int ,3> test_1{1,1,1};
    std::array<int,6> test_2{1,1,1,2,2,2};
    std::array<int,6> test_3{1,1,1,2,2,3};
    std::array<int,7> test_4{1,1,1,2,3,3,5};

    int res_1[]={1};
    int res_2[]={1,2};
    int res_3[]={1,2,3};
    int res_4[]={1,2,3,5};

    auto array_1 = GenListNOde(test_1);
    auto array_2 = GenListNOde(test_2);
    auto array_3 = GenListNOde(test_3);
    auto array_4 = GenListNOde(test_4);
    //display(array_1);
    auto ans_1 = Solution().deleteDuplicates(array_1);
    display(ans_1);
    auto ans_2 = Solution().deleteDuplicates(array_2);
    display(ans_2);
    auto ans_3 = Solution().deleteDuplicates(array_3);
    display(ans_3);
    auto ans_4 = Solution().deleteDuplicates(array_4);
    display(ans_4);
    return 1;
}