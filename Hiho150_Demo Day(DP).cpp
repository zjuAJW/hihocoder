	#include <iostream>
	#include <string>
	#include <stdio.h>  
	#include <stdlib.h>  
	#include <vector>
	#include <algorithm>

	using namespace std;

	void solve(vector<vector<char>>& maze, vector<vector<vector<int>>>& result) {
		int N = maze.size();
		int M = maze[0].size();
		for (int j = 1; j < M - 1; j++) {
			int left_right_right = result[0][j - 1][0] + (maze[0][j] != '.');
			int left_down_right = result[0][j - 1][1] + (maze[1][j - 1] != 'b') + (maze[0][j] != '.');
			result[0][j][0] = min(left_right_right,left_down_right);
			int left_right_down = result[0][j - 1][0] + (maze[0][j] != '.') + (maze[0][j + 1] != 'b');
			int left_down_down = result[0][j - 1][1] + (maze[0][j] != '.') + (maze[1][j - 1] != 'b') + (maze[0][j + 1] != 'b');
			result[0][j][1] = min(left_right_down, left_down_down);
		}

		int left_right_right = result[0][M - 2][0] + (maze[0][M-1] != '.');
		int left_down_right = result[0][M - 2][1] + (maze[0 + 1][M - 2] != 'b') + (maze[0][M-1] != '.');
		int left_right_down = result[0][M - 2][0] + (maze[0][M-1] != '.');
		int left_down_down = result[0][M - 2][1] + (maze[0][M-1] != '.') + (maze[0 + 1][M - 2] != 'b');
		result[0][M-1][0] = min(left_right_right, left_down_right);
		result[0][M-1][1] = min(left_right_down, left_down_down);

		for (int i = 1; i < N; ++i) {
			for (int j = 0; j < M - 1; ++j) {
				//单独处理最后一行
				if (i == N - 1) {
					int up_right_right = result[i - 1][j][0] + (maze[i][j] != '.') + (maze[i - 1][j + 1] != 'b');
					int up_down_right = result[i - 1][j][1] + (maze[i][j] != '.');
					int up_right_down = result[i - 1][j][1] + (maze[i][j] != '.') + (maze[i - 1][j + 1] != 'b');
					int up_down_down = result[i - 1][j][1] + (maze[i][j] != '.');
					if (j == 0) {
						result[i][j][1] = min(up_right_down, up_right_down);
						result[i][j][0] = min(up_right_right, up_down_right);
					}
					else {
						int left_right_right = result[i][j - 1][0] + (maze[i][j] != '.');
						int left_down_right = result[i][j - 1][1] + (maze[i][j] != '.');
						int left_right_down = result[i][j - 1][0] + (maze[i][j] != '.') + (maze[i][j + 1] != 'b');
						int left_down_down = result[i][j - 1][1] + (maze[i][j] != '.') + (maze[i][j + 1] != 'b');
						result[i][j][0] = min(min(up_right_right, up_down_right), min(left_right_right, left_down_right));
						result[i][j][1] = min(min(up_right_down, up_down_down), min(left_right_down, left_down_down));
					}
				}
				else {

					//除去最后一行和最后一列中间的部分
					int up_right_right = result[i - 1][j][0] + (maze[i][j] != '.') + (maze[i - 1][j + 1] != 'b') + (maze[i + 1][j] != 'b');
					int up_down_right = result[i - 1][j][1] + (maze[i][j] != '.') + (maze[i + 1][j] != 'b');
					int up_right_down = result[i - 1][j][1] + (maze[i][j] != '.') + (maze[i - 1][j + 1] != 'b');
					int up_down_down = result[i - 1][j][1] + (maze[i][j] != '.');
					if (j == 0) {
						result[i][j][1] = min(up_right_down, up_right_down);
						result[i][j][0] = min(up_right_right, up_down_right);
					}
					else {
						int left_right_right = result[i][j - 1][0] + (maze[i][j] != '.');
						int left_down_right = result[i][j - 1][1] + (maze[i + 1][j - 1] != 'b') + (maze[i][j] != '.');
						int left_right_down = result[i][j - 1][0] + (maze[i][j] != '.') + (maze[i][j + 1] != 'b');
						int left_down_down = result[i][j - 1][1] + (maze[i][j] != '.') + (maze[i + 1][j - 1] != 'b') + (maze[i][j + 1] != 'b');
						result[i][j][0] = min(min(up_right_right, up_down_right), min(left_right_right, left_down_right));
						result[i][j][1] = min(min(up_right_down, up_down_down), min(left_right_down, left_down_down));
					}
				}

			}

			if (i == N - 1) {
				int up_right_right = result[i - 1][M - 1][0] + (maze[i][M - 1] != '.');
				int up_down_right = result[i - 1][M - 1][1] + (maze[i][M - 1] != '.');
				int up_right_down = result[i - 1][M - 1][1] + (maze[i][M - 1] != '.');
				int up_down_down = result[i - 1][M - 1][1] + (maze[i][M - 1] != '.');
				int left_right_right = result[i][M - 1 - 1][0] + (maze[i][M - 1] != '.');
				int left_down_right = result[i][M - 1 - 1][1] + (maze[i][M - 1] != '.');
				int left_right_down = result[i][M - 1 - 1][0] + (maze[0][M - 1] != '.');
				int left_down_down = result[i][M - 1 - 1][1] + (maze[i][M - 1] != '.');
				result[i][M - 1][0] = min(min(up_right_right, up_down_right), min(left_right_right, left_down_right));
				result[i][M - 1][1] = min(min(up_right_down, up_down_down), min(left_right_down, left_down_down));
			}
			else {
				//单独处理最后一列
				int up_right_right = result[i - 1][M - 1][0] + (maze[i][M - 1] != '.') + (maze[i + 1][M - 1] != 'b');
				int up_down_right = result[i - 1][M - 1][1] + (maze[i][M - 1] != '.') + (maze[i + 1][M - 1] != 'b');
				int up_right_down = result[i - 1][M - 1][1] + (maze[i][M - 1] != '.');
				int up_down_down = result[i - 1][M - 1][1] + (maze[i][M - 1] != '.');
				int left_right_right = result[i][M - 1 - 1][0] + (maze[i][M - 1] != '.');
				int left_down_right = result[i][M - 1 - 1][1] + (maze[i + 1][M - 1 - 1] != 'b') + (maze[i][M - 1] != '.');
				int left_right_down = result[i][M - 1 - 1][0] + (maze[0][M - 1] != '.');
				int left_down_down = result[i][M - 1 - 1][1] + (maze[i][M - 1] != '.') + (maze[i + 1][M - 1 - 1] != 'b');
				result[i][M - 1][0] = min(min(up_right_right, up_down_right), min(left_right_right, left_down_right));
				result[i][M - 1][1] = min(min(up_right_down, up_down_down), min(left_right_down, left_down_down));
			}
		}
	}

	int main() {
		int N, M;
		cin >> N >> M;
		vector<vector<char>> maze(N);
		vector<vector<vector<int>>> result;
		result.resize(N);
		for (int i = 0; i < N; ++i) {
			result[i].resize(M);
			for (int j = 0; j < M; ++j) {
				result[i][j].resize(2);
			}
		}
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < M; ++j) {
				char c;
				cin >> c;
				maze[i].push_back(c);
			}
		}
		solve(maze, result);
		cout << min(result[N - 1][M - 1][0], result[N - 1][M - 1][1]) << endl;
	}


