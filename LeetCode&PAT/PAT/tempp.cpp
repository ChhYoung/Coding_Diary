#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct student{
	long long int reg_num;
	int sco;
	int loc_num;
	int final_rank = 0;
	int loc_rank = 0;
	
	student(string reg_num_,int scor_,int loc_num_) :
		reg_num(reg_num_),
		sco(sco_),
		loc_num(loc_num_)
		{}
};

bool cmp_1(student a, student b){
	return a.sco != b.sco ? (a.sco > b.sco)  :  (a.reg_num < b.reg_num);
}




int main(){
	// location
	int N;
	scanf("%d",&N);
	vector<student> total;
	for(int i=1; i<=N; ++i){
		int num;
		cin>>num;
		for(int j=1; j<=num; ++j){
			long long int a;
			int sco;
			cin>>a>>sco;
			total.push_back({a,sco,j});
		}
		sort(total.begin(), total.end(),cmp_1);
		for(int i=1; i<=total.size(); ++i){
			total[i-1].loc_rank = i;
		}
	} 
}