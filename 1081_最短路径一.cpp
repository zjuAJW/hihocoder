/*
经典的dijkstra算法
唯一要注意的是题目的描述：两点之间的路径肯能会有很多条，而且是无向的。
 */

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

const int INF = 1000000;
int N, M, S, T;
int collected[1005];
int dis[1005];
int map[1005][1005];

void dijkstra(int S, int N) {

    while (true) {
        int v = -1;
        for (int i = 1; i <= N; ++i) {
            if (!collected[i] && (v == -1 || dis[i] < dis[v])) v = i;
        }

        if (v == -1) return;
        collected[v] = 1;
        for (int i = 1; i <= N; ++i) {
            if (!collected[i] && map[v][i] != INF && dis[i] > dis[v] + map[v][i]) {
                dis[i] = dis[v] + map[v][i];
            }
        }
    }
}

int main() {
    cin >> N >> M >> S >> T;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            map[i][j] = INF;

    for (int i = 0; i < M; ++i) {
        int x, y, dis;
        cin >> x >> y >> dis;
        if (dis < map[x][y]) {
            map[x][y] = dis;
            map[y][x] = dis;
        }
    }

    for (int i = 1; i <= N; ++i) {
        dis[i] = map[S][i];
        collected[i] = 0;
    }

    dis[S] = 0;
    collected[S] = 1;

    dijkstra(S, N);
    cout << dis[T] << endl;

    return 0;
}
    