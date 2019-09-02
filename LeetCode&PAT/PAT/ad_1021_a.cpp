#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
int n, maxheight = 0;
// 邻接表
vector<vector<int>> v;
// 记录是否已经访问
bool visit[10010];

set<int> s;
vector<int> temp;

void dfs(int node, int height) {
    if(height > maxheight) {
        temp.clear();
        temp.push_back(node);
        maxheight = height;
    } else if(height == maxheight){
        temp.push_back(node);
    }
    visit[node] = true;
    for(int i = 0; i < v[node].size(); i++) {
        if(visit[v[node][i]] == false)
            dfs(v[node][i], height + 1);
    }
}

int main() {
    scanf("%d", &n);
    v.resize(n + 1);
    // s1 来记录第一次找到的端点
    int a, b, cnt = 0, s1 = 0;
    
    for(int i = 0; i < n - 1; i++) {
        scanf("%d%d", &a, &b);
        // 加入边 a->b, b->a
        v[a].push_back(b);
        v[b].push_back(a);
    }

    // 对与所有节点，通过dfs遍历其联通域，用cnt来记录联通域的数量
    for(int i = 1; i <= n; i++) {
        if(visit[i] == false) {
            dfs(i, 1);
            if(i == 1) {
                if (temp.size() != 0) s1 = temp[0];
                for(int j = 0; j < temp.size(); j++)
                    // s中先存储第一次找到的端点
                    s.insert(temp[j]);
            }
            // 记录联通域数量
            cnt++;
        }
    }

    if(cnt >= 2) {
        printf("Error: %d components", cnt);
    } else {
        temp.clear();
        maxheight = 0;
        fill(visit, visit + 10010, false);
        // 从第一次的端点出发，再经过一次dfs ，找到第二个端点
        // 依然保存在 temp 中
        dfs(s1, 1);
        for(int i = 0; i < temp.size(); i++)
            // s中存储第二次找到的端点
            s.insert(temp[i]);
        for(auto it = s.begin(); it != s.end(); it++)
            printf("%d\n", *it);
    }
    return 0;
}