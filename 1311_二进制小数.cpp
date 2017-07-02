/*
十进制小数转二进制小数我们可以模拟“乘2减1”的手算过程。例如对于0.6875，这个“乘2减1”的过程是这样的，每次将当前小数乘以2，如果结果大于等于1，那么将结果减1：

 0.6875
x     2
=1.375    减去整数部分    1

 0.375
x    2
=0.75     减去整数部分    0

 0.75
x   2
=1.5      减去整数部分    1

 0.5
x  2
=1.0      减去整数部分    1

 0        结束
经过4次“乘2减1”的操作，结果变为0。我们依次减去的整数部分是1011，所以对应的二进制小数就是0.1011。

假设X的小数部分有N位，如果我们经过N次操作结果仍不为0，那么X就不能表示成有限位数的二进制小数。

考虑到X的小数部分可能有100位，我们实现这个模拟手算的过程需要用“高精度”计算的方法：用一个数组去保存每一位数字，然后按位进行乘以2的操作。
*/

#include <iostream>
#include <iterator>
#include <string>

using namespace std;

void Double(string& num) {
	int carry = 0;
	for (auto rbeg = num.rbegin(); rbeg != num.rend(); ++rbeg) {
		if (*rbeg != '.') {
			auto x = (*rbeg - '0') * 2 + carry;
			if (x >= 10) {
				*rbeg = '0' + (x - 10);
				carry = 1;
			}
			else {
				*rbeg = '0' + x;
				carry = 0;
			}
		}
	}
}

int main() {
	int N;
	cin >> N;
	for (int i = 0; i < N; ++i) {
		string num;
		cin >> num;
		string result = "";
		for (int i = 0; i < num.size() - 2; ++i) {
			Double(num);
			result += num[0];
			num[0] = '0';
		}
		int earlyBreak = 0;
		for (auto n : num) {
			if (n != '0' && n != '.') {
				cout << "NO" << endl;
				earlyBreak = 1;
				break;
			}
		}
		if (!earlyBreak)
			cout << "0." + result << endl;
	}

}



