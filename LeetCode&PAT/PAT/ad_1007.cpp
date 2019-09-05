#include<iostream>
#include<vector>
using namespace std;

int main(){
    int k;
    cin>>k;
    vector<int> vec(k);
    for(int i=0; i<k; ++i){
        cin>>vec[i];
    }

    int sum = -1, lindex=0, rindex=k-1, temp=0, tempindex = 0;
    for(int i=0; i<k; ++i){
        temp = temp + vec[i];
        if(temp < 0){
            temp = 0;
            tempindex = i+1;
        }
        else if(temp > sum){
            sum = temp;
            lindex = tempindex;
            rindex = i;
        }
    }
    if(sum < 0) sum = 0;
    cout<<sum<<' '<<vec[lindex]<<' '<<vec[rindex];
    return 0;
}