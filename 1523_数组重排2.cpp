#include <iostream>
#include <string>
#include <stdio.h>  
#include <stdlib.h>  
#include <vector>
#include <algorithm>

using namespace std;
int main() {
	int N;
	cin >> N;
	int num[100000];
	int snum[100000];
	for (int i = 0; i < N; ++i) {
		cin >> num[i];
		snum[i] = num[i];
	}
	sort(snum, snum + N);
	int result = N;
	int i = N - 1;
	for (int j = N - 1; j >= 0; --j) {
		if (num[j] == snum[i]) {
			--i;
			--result;
		}
	}
	cout << result << endl;
}
