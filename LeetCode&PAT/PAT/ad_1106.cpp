#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

vector<int> node[100000];
int min_depth = 99999999, min_num = 1;

void dfs(int index, int level){
    if(min_depth < level) 
        return;
    if(node[index].size() == 0){
        if(level == min_depth){
            min_num++;
        }
        if(level <  min_depth){
            min_depth = level;
            min_num = 1;
        }
        return ;
    }
    for(int i=0;i<node[index].size();++i){
        dfs(node[index][i],level+1);
    }
}

int main(){
    int n,temp;
    double p,r;
    cin>>n>>p>>r;

    for(int i=0; i<n; ++i){
        int k;
        cin>>k;
        for(int j=0; j<k ;++j){
            int input;
            cin>>input;
            node[i].push_back(input);
        }
    }

    dfs(0,0);
    printf("%.4f %d", p * pow(1 + r/100, min_depth), min_num);
    return 0;
}