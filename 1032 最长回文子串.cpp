/*
最长回文子串问题，采用了manacher算法。
manacher算法思路是利用回文字串的对称性，逐渐向右扩展右边界。
*/


#include <string>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int manacher(string &s) {
	string s1 = "#";
	for (auto i : s) {
		s1 += i;
		s1 += "#";
	}
	vector<int> length(s1.length(),0);	//记录以每个字符为中心的最长回文串的长度
	int max = 1;	//记录最长回文串的长度
	int max_right = 0;	//记录到达的右边界
	int pos = 0;	//记录到达右边界的回文串的中心位置
	for (int i = 0; i < s1.length();++i) {
		if (i < max_right) {		//如果当前位置在右边界的左侧，那么找到其关于pos的对称点，利用对称点的串长度信息
			length[i] = min(length[2 * pos - i], max_right - i + 1); 
		}
		while (i + length[i] < s1.length() && i - length[i] >= 0) {
			if (s1[i + length[i]] == s1[i - length[i]])
				++length[i];
			else
				break;
		}
		if (i + length[i] - 1 > max_right) {
			max_right = i + length[i] - 1;	
			pos = i;
		}
		max = max > length[i] ? max : length[i];
	}
	return max - 1;
}
int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		string s;
		cin >> s;
		cout << manacher(s) << endl;
	}
}