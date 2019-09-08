#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn = 510;
const int inf = 99999999;
int n, m, s, d;
int edge[maxn][maxn], cost[maxn][maxn], dis[maxn], c[maxn];
bool visit[maxn];

int pre[maxn] = { -1 };

int main() {
	fill(edge[0], edge[0] + maxn * maxn, inf);
	fill(dis, dis + maxn, inf);
	cin>>n>>m>>s>>d;
    if(s == d) {
        cout<<s<<' '<<d<<' '<<0;
        return 0;
    }

	for(int i=0;i<m;++i){
		int c1,c2,dis1,cos;
		cin>>c1>>c2>>dis1>>cos;
		edge[c1][c2]=edge[c2][c1]=dis1;
		cost[c1][c2]=cost[c2][c1]=cos;
	}
	dis[s] = 0;
	c[s] = 0;
	for (int i = 0; i < n; ++i) {
		int u = -1, minn = inf;
		for (int j = 0; j < n; ++j) {
			if (visit[j] == false && dis[j] < minn) {
				u = j;
				minn = dis[j];
			}
		}
		if (u == -1) break;
		visit[u] = true;
		for (int v = 0; v < n; ++v) {
			if (visit[v] == false && edge[u][v] != inf) {
				if (dis[v] > dis[u] + edge[u][v]) {
					dis[v] = dis[u] + edge[u][v];
					c[v] = c[u] + cost[u][v];
					pre[v] = u;
				}
				else if (dis[v] == dis[u] + edge[u][v]) {
					// 比较cost 再看是否应该加入到路径中
					if (c[v] > c[u] + cost[u][v]) {
						pre[v] = u;
						c[v] = c[u] + cost[u][v];
					}
				}
			}
		}
	}
	vector<int> res;
	int i = d;
	while (i != s) {
		res.push_back(i);
		i = pre[i];
	}
	res.push_back(s);
	for (int i = res.size()-1; i >= 0; i--) {
		cout << res[i] << ' ';
	}
	cout << dis[d] << ' ' << c[d];
    return 0;
}