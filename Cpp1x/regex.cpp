#include <iostream>
#include <string>
#include <regex>
#include <vector>

using namespace std;

int test_regex_match() {
	string pattern{ "\\d{3}-\\d{8}|\\d{4}-\\d{7}" };
	regex re(pattern);
	vector<string> str{ "010-12345678", "0319-9876543", "021-123456789" };
	for (auto& tmp : str) {
		bool ret = regex_match(tmp, re);
		if (ret) printf("%s, can match\n", tmp.c_str());
		else printf("%s, cannot match\n", tmp.c_str());
	}
	return 0;
}


int test_regex_search() {
	string pattern{ "http|https://\\w*$" };
	regex re(pattern);

	vector<string> str{ "http://blog.csdn.net/fengbingchun", "https://github.com/fengbingchun",
		"abcd://124.456", "abcd https://github.com/fengbingchun 123" };
	for (auto tmp : str) {
		bool ret = regex_search(tmp, re);
		if(ret) printf("%s, can search\n", tmp.c_str());
		else printf("%s, cannot search\n", tmp.c_str());
	}
	return 0;
}


int test_regex_search2() {
	string pattern{ "[a-zA-Z]+://[^\\s]*" };
	regex re(pattern);
	string str{ "my csdn blog addr is: http://blog.csdn.net/fengbingchun , my github addr is: https://github.com/fengbingchun " };
	smatch results;
	while (regex_search(str, results, re)) {
		for (auto& x : results) {
			cout << x << " ";
		}
		cout << endl;
		str = results.suffix().str();
	}
	return 0;
}


int test_regex_replace() {
	string pattern{ "\\d{18}|\\d{17}X" };
	regex re(pattern);
	vector<string> str{ "123456789012345678", "abcd123456789012345678efgh",
		"abcdefbg", "12345678901234567X" };
	string fmt{ "********" };
	for (auto& tmp : str) {
		string ret = regex_replace(tmp, re, fmt);
		printf("src: %s, dst: %s\n", tmp.c_str(), ret.c_str());
	}
	return 0;
}


int test_regex_replace2() {
	string s{ "there is a subsequence in the string\n" };
	regex e("\\b(sub)([^\\s]*)");
	cout << regex_replace(s, e, "sub-$2");
	string result;
	regex_replace(back_inserter(result), s.begin(), s.end(), e, "$2");
	cout << result;

	cout << regex_replace(s, e, "$1 and $2", regex_constants::format_no_copy);
	cout << endl;
	return 0;
}


int main() {
	test_regex_match();
	cout << '\n';
	test_regex_search();
	cout << '\n';
	test_regex_search2();
	cout << '\n';
	test_regex_replace();
	cout << '\n';
	test_regex_replace2();
}
