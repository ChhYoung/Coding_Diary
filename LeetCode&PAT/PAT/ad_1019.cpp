 /*
#include <cstdio>
#include<iostream>
using namespace std;
int main() {
    
	int a, b;
	scanf("%d %d", &a, &b);
	int arr[40], index = 0;
	while(a != 0) {
		arr[index++] = a % b;
		a = a / b;
	}
	int flag = 0;
	for(int i = 0; i < index / 2; i++) {
		if(arr[i] != arr[index-i-1]) {
			printf("No\n");
			flag = 1;
			break;
		}
	}
	if(!flag) printf("Yes\n");
	for(int i = index - 1; i >= 0; i--) {
		printf("%d", arr[i]);
		if(i != 0) printf(" ");
	}
	if(index == 0)
		printf("0");

	return 0;
}


*/

#include<iostream>
#include<vector>
using namespace std;

int reverse(int a,int d=10) {
	int res = 0;
	while (a) {
		res = res * d + a % d;
		a /= d;
	}
	return res;
}

int main(){
    int a,b;
    cin>>a>>b;
    int rev = reverse(a,b);

    if(a == rev){
        cout<<"Yes\n";
    }
    else {
        cout<<"No\n";
    }

    if(a == 0)
        cout<<0;
    else{
        vector<int> res;
        while(a){
            res.push_back(a%b);
            a /= b;
        }
        for(int i=res.size()-1;i>=1;--i){
            cout<<res[i]<<" ";
        }
        cout<<res[0];
    }
    return 0;
}
