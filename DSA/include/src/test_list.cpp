#include<iostream>
#include"list.h"
#include<vector>
#include<ctime>

int main(){
    /* test for time 
    clock_t time;
    //  code ....
    std::cout<<(((double)clock() - start) / CLOCKS_PER_SEC)<<"\n\n";
    
     */
    std::vector<int> vec_1 = {1,2,3,4,5,6,7,8};
    DSA::List<int> t_list_1(vec_1);
    /* 
    for(int i:vec_1)
        t_list_1.insert_as_last(i);
    */
    t_list_1.print();
     
    t_list_1.reverse();
    t_list_1.print();

    return 1;
}