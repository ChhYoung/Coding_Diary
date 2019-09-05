#include<iostream>
#include<algorithm>
using namespace std;
int book[210], dp[10010], a[10010];

int main() {
	int n, m;
	cin >> n >> m;
	fill(book, book + 210, -1);
	for (int i = 0; i < m; ++i) {
		int temp;
		cin >> temp;
		book[temp] = i;
	}
	int l;
	cin >> l;
	int num = 0;
	for (int i = 0; i < l; ++i) {
		int index;
		cin >> index;
		if (book[index] != -1) {
			a[num++] = book[index];
		}
	}
	int maxL = -1;
    // LIS的固定解法
	for (int i = 0; i < num; ++i) {
        // 每次初始化i长度的子问题的长度
		dp[i] = 1;
        // 对于i长的子问题，从头开始检查
		for (int j = 0; j < i; ++j) {
            // 状态转移
			if (a[j] <= a[i]) {
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		maxL = max(dp[i], maxL);
	}

	cout << maxL;
	return 0;
}