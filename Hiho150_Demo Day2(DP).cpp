#include <iostream>
#include <string>
#include <stdio.h>  
#include <stdlib.h>  
#include <vector>
#include <algorithm>

using namespace std;

void solve(vector<vector<char>>& maze, vector<vector<vector<int>>>& result) {
	int N = maze.size() - 2;
	int M = maze[0].size() - 2;
	for (int i = 1; i < N + 1; ++i) {
		for (int j = 1; j < M + 1; ++j) {
			if (i == 1 && j == 1) {
				result[i][j][1] = 0;
				result[i][j][0] = 1;
			}
			else {
				int up_right_right = result[i - 1][j][0] + (maze[i][j] != '.') + (maze[i - 1][j + 1] != 'b') + (maze[i + 1][j] != 'b');
				int up_down_right = result[i - 1][j][1] + (maze[i][j] != '.') + (maze[i + 1][j] != 'b');
				int up_right_down = result[i - 1][j][0] + (maze[i][j] != '.') + (maze[i - 1][j + 1] != 'b');
				int up_down_down = result[i - 1][j][1] + (maze[i][j] != '.');
				int left_right_right = result[i][j - 1][0] + (maze[i][j] != '.');
				int left_down_right = result[i][j - 1][1] + (maze[i][j] != '.') + (maze[i + 1][j - 1] != 'b');
				int left_right_down = result[i][j - 1][0] + (maze[i][j] != '.') + (maze[i][j + 1] != 'b');
				int left_down_down = result[i][j - 1][1] + (maze[i][j] != '.') + (maze[i + 1][j - 1] != 'b') + (maze[i][j + 1] != 'b');
				result[i][j][0] = min(min(up_right_right, up_down_right), min(left_right_right, left_down_right));
				result[i][j][1] = min(min(up_right_down, up_down_down), min(left_right_down, left_down_down));
			}
		}
	}
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<vector<char>> maze(N + 2);
	vector<vector<vector<int>>> result;
	result.resize(N + 2);
	result[0] = vector<vector<int>>(M + 2, vector<int>(2,100000000));
	result[N + 1] = vector<vector<int>>(M + 2, vector<int>(2, 100000000));
	for (int i = 1; i < N + 1; ++i) {
		result[i].resize(M + 2);
		result[i][0] = vector<int>(2, 100000000);
		for (int j = 1; j < M + 1; ++j) {
			result[i][j].resize(2);
		}
		result[i][M + 1] = vector<int>(2, 100000000);
	}

	maze[0] = vector<char>(M + 2, 'b');
	maze[N + 1] = vector<char>(M + 2, 'b');
	for (int i = 1; i < N + 1; ++i) {
		maze[i].push_back('b');
		for (int j = 1; j < M + 1; ++j) {
			char c;
			cin >> c;
			maze[i].push_back(c);
		}
		maze[i].push_back('b');
	}
	solve(maze, result);
	cout << min(result[N][M][0], result[N][M][1]) << endl;
}