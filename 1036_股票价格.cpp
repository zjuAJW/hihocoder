/*
这道题利用了C++ map和set的有序性，实现起来比较简单，主要就看脑袋能不能转过弯了
*/
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>
#include <math.h>
#include <cstring>
#include <set>

using namespace std;

int main() {
	int N;
	cin >> N;
	map<int, int> price;
	multiset<int> prices;
	for (int i = 0; i < N; ++i) {
		char c;
		cin >> c;
		if (c == 'P') {
			int t, p;
			cin >> t >> p;
			price[t] = p;
			prices.insert(p);
		}
		else if (c == 'R') {
			int t;
			cin >> t;
			while (!price.empty() && (price.begin())->first <= t) {
				auto ite = prices.find(price.begin()->second);
				prices.erase(ite);
				price.erase(price.begin());
			}
		}
		else if (c == 'Q') {
			cout << *(prices.rbegin()) << ' ' << *(prices.begin()) << ' ' << price.rbegin()->second << endl;
		}
	}

}



