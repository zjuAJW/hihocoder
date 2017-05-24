// Problem.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <map>
#include <math.h>
#include <stack>
#include <cstring>

using namespace std;

#define FORINT(i,s,t) for(int i=s;i<=t;i++)
const int l = 102;
bool exist[l][l][l];
bool outside[l][l][l];
struct p3 {
	p3() {};
	p3(int a, int b, int c) :x(a), y(b), z(c) {}
	int x, y, z;
};
stack<p3> points;
stack<p3> fillstack;
//第一个条件
bool adj(int x, int y, int z)
{
	if (exist[x][y][z])
		return false;
	if (z == 1)
		return true;
	return exist[x - 1][y][z] || exist[x + 1][y][z] ||
		exist[x][y - 1][z] || exist[x][y + 1][z] ||
		exist[x][y][z - 1] || exist[x][y][z + 1];
}
//泛洪
void ffill(int x, int y, int z)
{
	p3 p(x, y, z);
	fillstack.push(p);
	while (!fillstack.empty())
	{
		p3 temp = fillstack.top();
		fillstack.pop();
		int x = temp.x, y = temp.y, z = temp.z;
		if (x<0 || x>101 || y<0 || y>101 || z<1 || z>101)
			continue;
		if (outside[x][y][z] || exist[x][y][z])
			continue;
		outside[x][y][z] = true;
		fillstack.push(p3(x + 1, y, z));
		fillstack.push(p3(x - 1, y, z));
		fillstack.push(p3(x, y + 1, z));
		fillstack.push(p3(x, y - 1, z));
		fillstack.push(p3(x, y, z + 1));
		fillstack.push(p3(x, y, z - 1));
	}
}
int main() {
	int t;
	cin >> t;
	while (t--)
	{
		int n;
		cin >> n;
		memset(exist, 0, sizeof(exist));
		memset(outside, 0, sizeof(outside));
		while (!points.empty())
			points.pop();
		while (!fillstack.empty())
			fillstack.pop();
		bool earlyBreak = false;
		while (n--)
		{
			p3 p;
			cin >> p.x >> p.y >> p.z;
			if (!adj(p.x, p.y, p.z) && !earlyBreak)
			{
				cout << "No" << endl;
				earlyBreak = true;
			}
			points.push(p);
			exist[p.x][p.y][p.z] = true;
		}
		if (earlyBreak)
			continue;
		FORINT(x, 0, 101)
			FORINT(y, 0, 101)
			exist[x][y][0] = true;
		ffill(0, 0, 1);
		while (!points.empty())
		{
			p3 p = points.top();
			int x = p.x, y = p.y, z = p.z;
			points.pop();
			if (outside[x - 1][y][z] ||
				outside[x + 1][y][z] ||
				outside[x][y - 1][z] ||
				outside[x][y + 1][z] ||
				outside[x][y][z - 1] ||
				outside[x][y][z + 1])
			{
				exist[x][y][z] = false;
				ffill(x, y, z);
			}
			else
			{
				cout << "No" << endl;
				earlyBreak = true;
				break;
			}
		}
		if (earlyBreak)
			continue;
		cout << "Yes" << endl;
	}
	return 0;
}



