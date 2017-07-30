/*
这道题是一类区间问题的变体，我们先来看一道最基础的区间问题：

给定N个区间[S1, E1], [S2, E2], ... [SN, EN]，求这些区间并集的长度。

这道题通常的解法是，我们把这N个区间的2N个端点从左到右排列在数轴上P1, P2, ... P2N。
并且如果一个点Pi是原区间的左端点，我们就把它标记成绿色；如果是右端点，就标记成蓝色。

值得注意的是这2N个点中可能存在重合的点。比如假设有两个区间[1, 3]和[3, 5]，那么在3这个位置上就同时存在一个绿点(左端点)和蓝点(右端点)。
某些情况下我们在排序时需要特别处理重合的点，例如要保证蓝点都排在绿点之前。
不过本题我们无需特殊处理，重合的点无论谁在前谁在后都不影响结果。

这2N个点把数轴分成了2N+1段，(-INF, P1), (P1, P2), (P2, P3) ... (P2N-1, P2N), (P2N, +INF)。
每一段内部被原来区间集合覆盖的情况都是相同的。换句话说，不会出现(Pi, Pi+1)的左半部分被第1、3、5号区间覆盖，而右半部分只被第1、3号区间覆盖这种情况。

所以我们可以从左到右扫描每一段，令cnt计数器初始值=0。
当扫过一个绿点时，cnt++；扫过一个蓝点时cnt--。我们可以发点对于(Pi, Pi+1)这一段，处理完Pi时的cnt值恰好代表了这一段被几个原来的区间同时覆盖。

有了每一段的cnt值，我们可以做很多事情。例如要求区间并集的长度，我们可以找出所有cnt值大于0的段(Pi, Pi+1)，并把这些段的长度(Pi+1 - Pi)求和。

我们还可以知道哪段被覆盖了最多次：自然是cnt值最大的段。

对于给定的坐标X，我们可以在O(logN)的时间内求出X这个点被覆盖多少次：我们只需要在P1, P2, ... P2N中二分查找出X的位置，即Pi < X < Pi+1，那么(Pi, Pi+1)这一段的cnt值就是答案。(当X恰好是端点时需要特判，取决于给出的区间是开区间还是闭区间)

好了，我们回到《区间求差》这道题目。我们可以把A和B集合中2N+2M个端点都从左到右排列在数轴上。并且用4种颜色标记出每个点是A的左端点、A的右端点、B的左端点、B的右端点。

然后我们用两个计数器cntA和cntB来分别维护每一段被A集合中的区间覆盖多少次、以及被B集合的区间覆盖多少次。那么如果某一段(Pi, Pi+1)满足cntA>0且cntB=0，那么它一定是A-B的一部分。我们对于这些段的长度求和即可。

整个算法对于端点排序的部分复杂度是O(NlogN)的，对于从左到右扫描复杂度是O(N)的。总体复杂度是O(NlogN)。
*/

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>
#include <math.h>
#include <cstring>

using namespace std;

enum point_type {
	A_left,
	A_right,
	B_left,
	B_right
};
struct Point {
	Point(int _x, point_type _type) : x(_x),type(_type){}
	int x;
	point_type type;
	bool operator<(const Point& p) {
		return this->x < p.x;
	}
};

bool cmp(const Point& a, const Point& b) {
	return a.x < b.x;
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<Point> points;
	int x;
	for (int i = 0; i < N; ++i) {
		cin >> x;
		points.push_back(Point(x, A_left));
		cin >> x;
		points.push_back(Point(x, A_right));
	}
	for (int i = 0; i < M; ++i) {
		cin >> x;
		points.push_back(Point(x, B_left));
		cin >> x;
		points.push_back(Point(x, B_right));
	}

	sort(points.begin(), points.end(), cmp);

	vector<int> cntA;
	vector<int> cntB;
	int countA = 0, countB = 0;
	int count = 0;
	for (auto p : points) {
		switch (p.type) {
		case A_left:
			cntA.push_back(++countA);
			cntB.push_back(countB);
			break;
		case A_right:
			cntA.push_back(--countA);
			cntB.push_back(countB);
			break;
		case B_left:
			cntA.push_back(countA);
			cntB.push_back(++countB);
			break;
		case B_right:
			cntA.push_back(countA);
			cntB.push_back(--countB);
			break;
		}
	}

	int result = 0;
	for (int i = 0; i < points.size(); ++i) {
		if (cntA[i] > 0 && cntB[i] == 0) {
			result += (points[i + 1].x - points[i].x);
		}
	}

	cout << result << endl;

}



