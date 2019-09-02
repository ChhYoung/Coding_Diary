#include<cstdio>
#include<vector>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 10010;
// 邻接表
vector<int> G[N];
// 记录每个节点是否没某个集合的根节点
bool isRoot[N];

int father[N];

// 寻找x所在集合的根
int findFather(int x){
    int a = x;
    while(x != father[x])
        x = father[x];

    while(a != father[a]){
        int z = a;
        father[z] = x;
    }
    return x;
}

void Union(int a, int b){
    int faA = findFather(a);
    int faB = findFather(b);
    if(faA != faB){
        father[faA] = faB;
    }
}

void init(int n){
    for(int i=1; i<=n; ++i){
        father[i] = i;
    }
}

// 计算联通块的数量
int calBlock(int n){
    int Block = 0;
    for(int i=1; i<=n; ++i){
        isRoot[findFather(i)] = true;
    }
    for(int i=1; i<=n; ++i){
        Block += isRoot[i];
    }
    return Block;
}

// 最大高度
int maxH = 0;
// temp 临时存放dfs的最远节点结果，ans保存答案
vector<int> temp,Ans;

// 当前访问节点u, 当前树高 Height, 父节点pre
void dfs(int u, int Height,int pre){
    if(Height > maxH){
        temp.clear();
        temp.push_back(u);
        maxH = Height;
    }
    else if(Height == maxH){
        temp.push_back(u);
    }

    // 遍历子节点
    for(int i=0; i<=G[u].size(); ++i){
        // 无向图，跳过访问父节点
        if(G[u][i] == pre) continue;
        dfs(G[u][i],Height+1,u);
    }
}

int main(){
    int a,b,n;
    scanf("%d",&n);
    init(n);
    for(int i=1; i<n; ++i){
        scanf("%d %d",&a,&b);
        G[a].push_back(b);
        G[b].push_back(a);
        Union(a,b);
    }
    int Block = calBlock(n);
    if(Block != 1){
        printf("Error: %d components\n",Block);
    }
    else{
        // 通过两次dfs找到最大路径
        // 从一号节点开始，初始高度是-1
        dfs(1,1,-1);
        Ans = temp;
        // 从任意一个根开始遍历,
        dfs(Ans[0],1,-1);

        for(int i=0; i<temp.size(); ++i)
            Ans.push_back(temp[i]);

        sort(Ans.begin(), Ans.end());
        printf("%d\n",Ans[0]);
        for(int i=1; i<Ans.size(); ++i){
            if(Ans[i] != Ans.size()){
                printf("%d\n",Ans[i]);
            }
        }
    }
    return 0;
}