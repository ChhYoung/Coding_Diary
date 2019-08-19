#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

struct student{
    long long int no;
    int score , finrank, loca, locarank;
};

// 用于sort的函数
// 成绩相等比较学号
bool cmp1(student a, student b){
    return a.score != b.score ? a.score > b.score : a.no < b.no;
}

/* 思路：
    * 先对每个考场中的学生进行排名
    * 对所有考生进行排名
    * 按顺序计算总排名，计算所有考生的信息
*/

int main(){
    // n , m分别为考场数量，与考场中人数
    int n,m;
    //考场数量
    scanf("%d",&n);
    // 用来储存所有学生
    vector<student> fin;
    for(int i=1;i<=n;++i){
        scanf("%d",&m);
        vector<student> v(m);
        for(int j=0;j<m;++j){
            scanf("%lld %d",&v[j].no, &v[j].score);
            v[j].loca = i;
        }
        // 在该考场中进行排名
        sort(v.begin(),v.end(),cmp1);
        // 考场中第一名记为1
        v[0].locarank = 1;
        fin.push_back(v[0]);
        //对于考场中剩余考生，按照分数排名，若分数相等则与之前一样
        // 否则排名非秩+1
        for(int j=1;j<m;++j){
            v[j].locarank = (v[j].score == v[j-1].score) ? (v[j-1].locarank):(j+1);
            fin.push_back(v[j]);
        }
    }
    // 对总体进行排序
    sort(fin.begin(), fin.end(), cmp1);
    fin[0].finrank = 1;
    for(int j=1;j<fin.size();++j){
        fin[j].finrank = (fin[j].score == fin[j-1].score) ? (fin[j-1].finrank):(j+1);
    }
    printf("%d\n",fin.size());
    for(int i=0;i<fin.size();++i){
        printf("%013lld %d %d %d\n",fin[i].no,fin[i].finrank,fin[i].loca,fin[i].locarank);
    }
    return 0;

    
}