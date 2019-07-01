#include<iostream>
using namespace std;

int main() {
	float W, T, L;
	float product = 1.0;
	for (int j = 0; j < 3; ++j) {
		while (cin >> W >> T >> L) {
			if (W >= T && W >= L) {
				cout << 'W';
				product *= W;
			}
			else if (T >= W && T >= L) {
				cout << 'T';
				product *= T;
			}
			else if (L >= W && L >= T) {
				cout << 'L';
				product *= L;
			}
			cout << " ";
		}
	}
	float res = 2 * (product * 0.65 - 1);
	printf("%.2f", res);
	return 0;
}