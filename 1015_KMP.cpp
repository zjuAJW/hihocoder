/*
KMP算法，next数组的表示以及一些边界情况很坑。。。一不小心就写错了
 */


#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>

#include <math.h>
#include <stdio.h>
using namespace std;

void calNext(const string& pattern, vector<int>& next) {
	next.push_back(-1);
	for (int i = 1; i < pattern.size(); ++i) {
		int j = next[i - 1];
		while (j != -1 && pattern[i] != pattern[j + 1]) j = next[j];
		if (pattern[i] == pattern[j + 1]) next.push_back(j + 1);
		else next.push_back(-1);
	}
}

int kmp(const string &s, const string &pattern) {
	int result = 0;
	vector<int> next;
	calNext(pattern, next);
	int i = 0;
	int j = 0;
	while (i < s.size()) {
		while (j<pattern.size() && pattern[j] == s[i]) {
			++j;
			++i;
		}
		if (j == pattern.size()) {
			++result;
			j = next[j - 1] + 1;
		}
		else if(j == 0){
			++i;
		}
		else {
			j = next[j - 1] + 1;
		}
		
	}
	return result;
}


int main() {
	string s, pattern;
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> pattern >> s;
		cout << kmp(s, pattern) << endl;
	}
}