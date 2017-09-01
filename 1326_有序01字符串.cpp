/*
最终总会按照某位分段，前面位0，后面为1。那么改动的次数，就是分段的那位前面的1的个数和后面的0的个数的和。统计每一位前面的1的个数个后面的0的个数，找出和的最小值，就可以了。不需要考虑这一位本身是1还是0，因为不管是0还是1都不需要改变。 比如：

               0 0 1 0 1 0 0 1 0 1 1 1 0 1
前面的1的个数: 0 0 0 1 1 2 2 2 3 3 4 5 6 6
后面的0的个数: 6 5 5 4 4 3 2 2 1 1 1 1 0 0
个数和:        6 5 5 5 5 5 4 4 4 4 5 6 6 6
最小的和为4


*/



#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <cstring>

using namespace std;

int main()
{
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		int pre[1001], post[1001];
		int result = 1005;
		memset(pre, 0, sizeof(pre));
		memset(post, 0, sizeof(post));
		string s;
		cin >> s;
		for (int i = 0; i < s.size();++i) {
			if (s[i] == '1')
				pre[i + 1] = pre[i] + 1;
			else
				pre[i + 1] = pre[i];
		}
		for (int i = s.size() - 1; i > 0; --i) {
			if (s[i] == '0')
				post[i - 1] = post[i] + 1;
			else
				post[i - 1] = post[i];
		}

		for (int i = 0; i < s.size(); ++i)
			result = min(result, pre[i] + post[i]);

		cout << result << endl;

	}

	return 0;

}