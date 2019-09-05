#include<string>
#include<iostream>
#include<algorithm>
using namespace std;

int main() {
	const int maxn = 1010;
	//bool f[maxn][maxn] = { false };
	//string str = "Is PAT&TAP symmetric?";
	//string str = "";
	bool f[maxn][maxn];
	fill_n(&f[0][0], maxn * maxn, false);
	string str;
	cin >> str;
	size_t maxL = 1;
	for (int i = 0; i < str.length(); ++i) {
		f[i][i] = true;
		for (size_t j = 0; j < i; ++j) {
			f[j][i] = (str[j] == str[i] && (i - j < 2 || f[j + 1][i - 1]));
			if (f[j][i] && maxL < (i - j + 1)) {
				maxL = i - j + 1;
			}
		}
	}

	cout << maxL;
	return 0;
}