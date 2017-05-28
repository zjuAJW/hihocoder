/*
这一题首先要理解题意，只要输入的ip地址能够匹配某一条规则的前缀就可以了。
然后前缀这种东西，又存在Trie树这种结构可以方便的进行查询。
需要注意的就是掩码为0的这种特殊情况，以及ip转换为二进制的算法。
ip转换效率太低的话会超时，一开始用了一些奇奇怪怪的方法，效率结果还很低，不如最简单的直接扫一遍就好了。
*/

#include <iostream>
#include <string>
#include <stdio.h>  
#include <stdlib.h>  
#include <vector>
#include <algorithm>

using namespace std;

class TrieTreeNode {
public:
	TrieTreeNode() :allow("YES"),no(0),rule_flag(0) {
		for (int i = 0; i < 2; ++i) {
			next[i] = nullptr;
		}
	}
	int rule_flag;
	string allow;
	int no;
	TrieTreeNode * next[2];
};

void TrieInsert(TrieTreeNode * root, const string& s, string _allow, int _no) {
	if (!root)
		return;
	auto p = root;
	for (auto i : s) {
		if (p->next[i - '0'] == nullptr) {
			p->next[i - '0'] = new TrieTreeNode();
		}
		p = p->next[i - '0'];
	}
	if (p->rule_flag) return;
	p->rule_flag = 1;
	p->allow = _allow;
	p->no = _no;
}

string TrieFind(TrieTreeNode * root, const string& s) {
	if (!root)
		return "NO";
	auto p = root;
	int min = -1;
	string result = p->allow;
	for (auto i : s) {
		if (p->next[i - '0'] == nullptr)
			break;
		else
			p = p->next[i - '0'];
		if (p->rule_flag) {
			if (min == -1){
				min = p->no;
				result = p->allow;
			}
			else {
				if (p->no < min) {
					min = p->no;
					result = p->allow;
				}
			}
		}
	}
	return result;
}


// string d2b(int& num) {
// 	string binary = "";
// 	int x = 128;
// 	int n = num;
// 	for(int i = 0;i<8;i++){
// 		binary += (n / x + '0');
// 		n %= x;
// 		x /= 2;
// 	}
// 	return binary;
// }


string convertIP(const string& ip) {
	vector<int> num;
	int n = 0;
	for (auto c : ip) {
		if (c == '.' || c == '/') {
			num.push_back(n);
			n = 0;
		}
		else {
			n *= 10;
			n += c - '0';
		}
	}
	num.push_back(n);
	string result = "";
	int count = 0;
	int mask = 33;
	if (num.size() == 5) {
		mask = num[4];
	}
	for (int i = 0; i < 4; i++) {
		int x = 128;
		int n = num[i];
		for (int i = 0; i<8; i++) {
			if (count == mask)
				break;
			result += (n / x + '0');
			++count;
			n %= x;
			x /= 2;
		}
		if (count == mask)
			break;
	}
	return result;

}

int main() {
	int N, M;
	TrieTreeNode root;
	cin >> N >> M;
	string ip, allow;
	for (int i = 0; i < N; i++) {
		cin >> allow >> ip;
		allow = (allow == "allow" ? "YES" : "NO");
		TrieInsert(&root, convertIP(ip), allow, i);
	}
	for (int i = 0; i < M; i++) {
		cin >> ip;
		ip = convertIP(ip);
		cout << TrieFind(&root,ip) << endl;
	}
}


