/*
这一题的思路也是一道区间问题，只要找到重叠区间的最大值就可以了
需要注意的是，如果区间端点重合，需要让右端点排在左边。

*/

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <math.h>

using namespace std;
struct Point {
	Point() = default;
	Point(int _x, int _type):x(_x),type(_type){}
	int x;
	int type;
};

bool cmp(const Point& a, const Point& b) {
	if (a.x == b.x)
		return a.type > b.type;
	else
		return a.x < b.x;
}


int main() {
	int N;
	cin >> N;
	vector<Point> points;
	for (int i = 0; i < N; ++i){
		int x, y;
		cin >> x >> y;
		points.push_back(Point(x, 1));
		points.push_back(Point(y, 2));
	}

	sort(points.begin(), points.end(), cmp);

	int cnt = 0;
	vector<int> count;
	for (auto p : points) {
		if (p.type == 1)
			count.push_back(++cnt);
		else
			count.push_back(--cnt);
	}

	cout << *max_element(count.begin(), count.end()) << endl;

}



