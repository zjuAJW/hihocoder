/*
目前的程序是错的

 */




#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;

typedef pair<int, int> P;
char map[105][105];
int key_pos[105][105];
int dis[105][105][32];
int N, M, K;

class state {
public:
    P p;
    string keys;
    state(int x, int y, string _key) : p(x,y), keys(_key) {}
};

int bin2dec(const string& s) {
    int ret = 0;
    int base = 1;
    for (auto iter = s.rbegin(); iter != s.rend(); ++iter) {
        ret += base * (*iter - '0');
        base *= 2;
    }
    return ret;
}

int main() {

    cin >> N >> M >> K;
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    memset(map, '\0', sizeof(map));
    memset(key_pos, -1, sizeof(key_pos));
    memset(dis, -1, sizeof(dis));
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            cin >> map[i][j];

    for (int i = 0; i < K; ++i) {
        int x, y;
        cin >> x >> y;
        key_pos[x][y] = i;
    }

    state start(a, b, "000000");
    if (key_pos[a][b] != -1)
        start.keys[key_pos[a][b]] = '1';

    dis[a][b][bin2dec(start.keys)] = 0;
    queue<state> que;
    que.push(start);
    int dx[4] = { 1, 0, -1, 0 };
    int dy[4] = { 0, 1, 0, -1 };
    while (!que.empty()) {
        auto s = que.front();
        que.pop();
        if (s.p.first == c && s.p.second == d) {
            cout << dis[c][d][bin2dec(s.keys)];
            return 0;
        }
        for (int i = 0; i < 4; ++i) {
            int nx = s.p.first + dx[i];
            int ny = s.p.second + dy[i];
            auto nkeys = s.keys;
            if (key_pos[nx][ny] != -1)
                nkeys[key_pos[nx][ny]] = '1';
            if (nx >= 0 && nx < N && ny < M && ny >= 0) {
                if ((map[nx][ny] == '.' || (map[nx][ny] >= 'A' && map[nx][ny] <= 'Z' && s.keys[map[nx][ny] - 'A'] == '1')) && dis[nx][ny][bin2dec(nkeys)] == -1) {
                        que.push(state(nx,ny,nkeys));
                        dis[nx][ny][bin2dec(nkeys)] = dis[s.p.first][s.p.second][bin2dec(s.keys)] + 1;
                }
            }
        }
    }

    cout << -1 << endl;
    return 0;
}
    