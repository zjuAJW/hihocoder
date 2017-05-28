#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>

#include <math.h>
#include <stdio.h>
using namespace std;

void calNext(const string& pattern,vector<int>& next) {
	next.push_back(0);
	for (int i = 1; i < pattern.size(); ++i) {
		int j = next[i - 1];
		while (j != 0 && pattern[i] != pattern[j]) j = next[j - 1];
		if (pattern[i] == pattern[j]) next.push_back(j + 1);
		else next.push_back(0);
	}
}

int kmp(const string &s, const string &pattern) {
	int result = 0;
	vector<int> next;
	calNext(pattern, next);
	int i = 0;
	while(i <= s.length() - pattern.length()){
		int pos = i;
		int j = 0;
		while (j<pattern.length() && pattern[j] == s[pos]) {
			++j;
			++pos;
		}
		if (j == pattern.length()) {
			++result;
			++i;
		}else
			i = pos - next[j - 1] + 1;
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
