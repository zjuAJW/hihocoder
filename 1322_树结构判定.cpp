/*
本题要求判断给定的无向图是不是一棵树。

包含N个点M条边的无向图是树的充分必要条件是N=M+1且N个点连通。

所以本题的关键就是判断这N个点是不是连通在一起。

判断连通性一般也有两种方法。

一种是从一个点（比如1号点）开始进行DFS/BFS，搜索过程中把遇到的点都标记上，最后检查是不是N个点都被标记了。

另一种方法是用并查集，依次处理每一条边，把每条边的两个顶点都合并到一个集合里。最后检查是不是N个点都在同一个集合中。
*/



#include <iostream>
#include <vector>
#include <memory>
#include <cstring>

using namespace std;
int map[505][505];
int visited[505];

void dfs(int i, int N) {
	visited[i] = 1;
	for (int j = 1; j <=N; ++j) {
		if (map[i][j] == 1 && visited[j] == 0) {
			dfs(j, N);
		}
	}
}
int main()
{	
	int T;
	cin >> T;
	for (int k = 0; k < T; ++k) {
		memset(map, 0, sizeof(map));
		memset(visited, 0, sizeof(visited));
		int N, M;
		cin >> N >> M;
		int p, q;
		for (int i = 0; i < M; ++i) {
			cin >> p >> q;
			map[p][q] = map[q][p] = 1;
		}
		if (N != M + 1) {
			cout << "NO" << endl;
			continue;
		}
		dfs(1,N);
		int flag = 0;
		for(int i = 1;i<=N;++i){
			if (visited[i] == 0) {
				cout << "NO" << endl;
				flag = 1;
				break;
			}
		}
		if(flag == 0)
			cout << "YES" << endl;
	}

	return 0;
}