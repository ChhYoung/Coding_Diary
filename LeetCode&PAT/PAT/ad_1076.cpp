#include<vector>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn = 1010;
struct node{
    int id;
    int level;
};

// 邻接表
vector<node> G[maxn];
// 是否已经加过队列
bool inq[maxn] = {false};

// 利用 bfs
// start : 起始节点， L ： max level
int bfs(int start, int L){
    // 转发数
    int forwardNum = 0;
    queue<node> que;
    node st;
    st.id = start;
    st.level = 0;
    que.push(st);
    inq[st.id] = true;
    while(!que.empty()){
        auto Node = que.front();
        que.pop();
        for(int i=0; i<G[Node.id].size(); ++i){
            node next = G[Node.id][i];
            next.level = Node.level+1;
            if(inq[next.id] == false && next.level <= L){
                que.push(next);
                inq[next.id] = true;
                forwardNum++;
            }
        }
    }
    return forwardNum;
}

int main(){
    node user;
    int n, L, numFollower, idFollow;
    cin>>n>>L;
    for(int i=1; i<=n; ++i){
        user.id = i;
        cin>>numFollower;
        for(int j=0; j<numFollower; ++j){
            cin>>idFollow;
            G[idFollow].push_back(user);
        }
    }
    int numQuery,s;
    cin>>numQuery;
    for(int i=0; i<numQuery; ++i){
        fill(inq, inq+maxn, false);
        cin>>s;
        cout<<bfs(s,L)<<endl;
    }
    return 0;
}