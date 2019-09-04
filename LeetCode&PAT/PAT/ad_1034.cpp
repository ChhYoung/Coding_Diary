#include<iostream>
#include<map>
#include<string>

using namespace std;

const int maxn = 2010;

map<string, int> stringToInt;
map<int, string> intToString;
map<string, int> ans; // head -> 人数

// weight[u] 为某一点的权值
int G[maxn][maxn] = {0}, weight[maxn]={0};
bool visit[maxn] ;
int n,k,numPerson = 0; // numPerson 总人数




void dfs(int nowVisit, int& head, int& numMember, int& totalWeight){
    visit[nowVisit] = true;
    numMember++;
    if(weight[nowVisit] > weight[head]){
        head = nowVisit;
    }

    // 遍历每个节点
    for(int i=0; i<numPerson; ++i){
        if(G[nowVisit][i] > 0){
            totalWeight += G[nowVisit][i];
            // ---------------------------------------------------//
            // 删除访问过的边，防止二次访问
            G[nowVisit][i] = G[i][nowVisit] = 0;
            if(visit[i] == false){
                dfs(i,head,numMember,totalWeight);
            }
        }
    }
}

// 遍历全图，获取每个联通块的消息
void dfsTrav(){
    for(int i=1;i<numPerson; ++i){
        // 找到没有被访问过的节点
        if(visit[i] == false){
            int head = i, numMember = 0,totalWeight = 0;
            dfs(i,head,numMember,totalWeight);
            // 满足条件, ans总记录
            if(numMember > 2 && totalWeight > k){
                ans[intToString[head]] = numMember;
            }
        }
    }
}

// 返回姓名对应的编号
int stoifunc(string s){
    if(stringToInt[s] == 0){
        stringToInt[s] = numPerson;
        intToString[numPerson] = s;
        return numPerson++;
    }
    else{
        return stringToInt[s];
    }
}

int main(){
    int w;
    cin>>n>>k;
    string s1,s2;
    for(int i=0; i<n; ++i){
        cin>>s1>>s2>>w;
        int id1 = stoifunc(s1);
        int id2 = stoifunc(s2);
        weight[id1] += w;
        weight[id2] += w;
        G[id1][id2] += w;
        G[id2][id1] += w;
    }
    dfsTrav();
    cout<<ans.size()<<endl;
    for(auto it=ans.begin;it != ans.end(); ++it)
        cout<<it->first<<" "<<it->second<<endl;
    return 0;
}
