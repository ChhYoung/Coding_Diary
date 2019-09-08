#include<vector>
#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

const int maxn = 1010;
const int inf = 9999999;

int n, m, k, ds;
int e[maxn][maxn], d[maxn];
bool visit[maxn];


int main(){
    fill(e[0], e[0]+1010*1010, inf);
    fill(d, d+1010, inf);
    cin>>n>>m>>k>>ds;

    for(int i=0; i<k; ++i){
        int tempdis = 0;
        string s,t;
        cin>>s>>t>>tempdis;
        int a,b;
        if(s[0] == 'G'){
            s = s.substr(1);
            a = n + stoi(s);
        }
        else {
            a = stoi(s);
        }
        if(t[0] == 'G'){
            t = t.substr(1);
            b = n + stoi(t);
        }
        else {
            b = stoi(t);
        }
    }

    int ansid = -1;
    double ansdis = -1,  ansavg = inf;
    for(int index = n+1; index <= n+m; ++index){ 
        double mindis = inf, aver = 0;
        fill(d, d+1010, inf);
        fill(visit, visit+1010, false);
        d[index] = 0;
        for(int i=0; i<n+m; ++i){
            int u = -1, minn = inf;
            for(int j=1; j<= m+n; ++j){
                if(visit[j] == false && d[j] < minn){
                    u = j;
                    minn = d[j];
                }
            }
            if(u == -1) break;
            visit[u] = true;
            for(int v=1; v<n+m; ++v){
                if(visit[v] == false && d[v] > d[u]+e[u][v]){
                    d[v] = d[u] + e[u][v];
                }
            }
        }

        for(int i=1; i<=n; ++i){
            if(d[i] > ds){
                mindis = -1;
                break;
            }
            if(d[i] < mindis) mindis = d[i];
            aver += 1.0 * d[i];
        }

        if(mindis == -1) continue;
        aver /= n;
        if(mindis > ansdis){
            ansid = index;
            ansdis = mindis;
            ansavg = aver;
        }

        else if(mindis == ansdis && aver < ansavg){
            ansdis = index;
            ansavg = aver;
        }
    }

    if(ansid == -1){
        printf("No Solution");
    }
    else {
        printf("G%d\n%.1f %.1f",ansid-n, ansdis, ansavg);
    }
    return 0;
}