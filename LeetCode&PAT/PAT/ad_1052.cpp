#include<iostream>
#include<algorithm>

using namespace std;

struct node{
    int address,key,next;
    bool flag = false;
}NODES[100000];

bool cmp(node a,node b){
    // 将无效节点放到后面
    return !a.flag || !b.flag ? a.flag > b.flag : a.key < b.key;
}

int main(){
    int n, cnt=0, add,addr,key,next;
    scanf("%d %d",&n,&add);
    for(int i=0; i<n; ++i){
        scanf("%d %d %d",&addr,&key,&next);
        NODES[addr] = {addr,key,next,false};
    }

    for(int temp = add; temp != -1; temp=NODES[temp].next){
        NODES[temp].flag = true;
        ++cnt;
    }

    if(cnt == 0){
        printf("0 -1");
    } 
    else {
        sort(NODES,NODES+100000,cmp);
        printf("%d %05d\n",cnt,NODES[0].address);
        for(int i=0; i < cnt; ++i){
            printf("%05d %d ",NODES[i].address, NODES[i].key);
            if(i != cnt - 1)
                printf("%05d\n",NODES[i+1].address);
            else 
                printf("-1\n");
        }
    }
    return 0;
}
