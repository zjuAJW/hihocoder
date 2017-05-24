/*
	对于小数据，很容易想到用floodfill，只要每次放置方块的时候做一次floodfill看看能不能走到地图外即可。
	但对于大数据，这样的复杂度O(N*L^3)=O(10^11)显然是不能接受的。
	不妨转换一下思维：假设这些方块已经全部堆好了，那么如果按照原建造序列的逆序来把它们一个一个地『拆』掉。
	既然『建』的时候每一块都能碰到，自然『拆』的时候也是。
	然后你就会发现一个很直观的做法：先把所有『自由』的位置打上『自由』标记(floodfill)；
	对于『拆』的每一块，首先它必须与一块『自由』位置相连，然后在把它拆掉的同时将『因此而释放的空间也打上自由标记』，
	即，以它为起点做一次floodfill，但只碰触那些『被释放』的位置。不难发现，每个坐标至多被打上一次『自由』标记。
	于是这种做法的复杂度为O(N+L^3)=O(10^6)，问题解决。这个思维转换的重点在于发现一个事实：判断一个空间是否由开转闭很难，因为你得遍历整个边界；
	然而由闭转开很容易：只要打开一个口就行了。

作者：夏洋
链接：https://www.zhihu.com/question/42406890/answer/94388263
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

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

#define L 102
class point {
public:
	point(int _x, int _y, int _z) :x(_x), y(_y), z(_z) {}
	int x, y, z;
};

bool outside[L][L][L];
bool exist[L][L][L];

void floodFill(int x, int y, int z) {
	vector<point> fstack;
	fstack.push_back(point(x, y, z));
	while (!fstack.empty()) {
		auto p = fstack.back();
		fstack.pop_back();
		int x = p.x, y = p.y, z = p.z;
		if (x > 101 || x < 0 || y > 101 || y < 0 || z > 101 || z < 1)
			continue;
		if (outside[x][y][z] || exist[x][y][z])
			continue;
		outside[x][y][z] = 1;
		fstack.push_back(point(x - 1, y, z));
		fstack.push_back(point(x + 1, y, z));
		fstack.push_back(point(x, y - 1, z));
		fstack.push_back(point(x, y + 1, z));
		fstack.push_back(point(x, y, z - 1));
		fstack.push_back(point(x, y, z + 1));
	}
}

int adj(int x, int y, int z) {
	if (exist[x][y][z]) return 0;
	return exist[x - 1][y][z] ||
		exist[x + 1][y][z] ||
		exist[x][y + 1][z] ||
		exist[x][y - 1][z] ||
		exist[x][y][z + 1] ||
		exist[x][y][z - 1];
}

int available(const point & p) {
	int x = p.x, y = p.y, z = p.z;
	return outside[x - 1][y][z] ||
		outside[x + 1][y][z] ||
		outside[x][y + 1][z] ||
		outside[x][y - 1][z] ||
		outside[x][y][z + 1] ||
		outside[x][y][z - 1];
}

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; ++i) {
		vector<point> points;
		memset(exist, 0, sizeof(exist));
		memset(outside, 0, sizeof(outside));
		for (int i = 0; i < L; ++i)
			for (int j = 0; j < L; ++j)
				exist[i][j][0] = 1;
		int earlyBreak = 0;
		int M;
		cin >> M;
		for (int j = 0; j < M; ++j) {
			int x, y, z;
			cin >> x >> y >> z;
			if (!adj(x, y, z) && !earlyBreak) {
				cout << "No" << endl;
				earlyBreak = 1;
			}
			if (!earlyBreak) {
				points.push_back(point(x, y, z));
				exist[x][y][z] = 1;
			}
		}
		if (earlyBreak) continue;
		floodFill(101, 101, 101);
		while (!points.empty()) {
			auto p = points.back();
			if (!available(p)) {
				cout << "No" << endl;
				earlyBreak = 1;
				break;
			}
			else {
				points.pop_back();
				exist[p.x][p.y][p.z] = 0;
				floodFill(p.x, p.y, p.z);
			}
		}
		if (!earlyBreak) cout << "Yes" << endl;
	}
}
