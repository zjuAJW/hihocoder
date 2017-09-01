/*
首先我们需要分析INVALID的充分必要条件。容易看出充要条件是S中某个字符的数目超过了(|S|+1)/2。

换句话说，除非有一个字母数量 过多，否则一定可以有一个合法的重排方案。

例如样例"aaabc"，5个字符中有3个'a'。这个例子'a'的数量就在临界值上，我们必须在第1、3、5个位置上都放'a'才能把所有的'a'分隔开。如果'a'的数量再多1个，比如"aaaabc"，那就没办法把'a'都分隔开了，结果就是INVALID。

那么，当我们知道目前的S不是INVALID时，我们怎么求字典序最小的重排方案呢？ 这里我们可以使用一个贪心策略：我们按照'a'-'z'的顺序枚举第一个字符c，如果除去c之后，S的剩余的字符仍然>不是INVALID，那么我们就把第一个字符定为c。之后我们可以用同样的策略确定第二位、第三位……，只是在确定第二位、第三位……的时候还需要要求当前字符不能与之前定下来的字符相同。

举个例子，假设S="bbbac"，我们知道出现最多的'b'一共出现了3次，没超过(|S|+1)/2=3，所以至少存在一种重排方案。这时我们要确定重排之后的第一个字符。由于我们希望字典序最小，所以我们 会先尝试第一个字符是'a'行不行。假设第一个字符是'a'，那么剩余的S'="bbbc"，这时剩余的S是INVALID，所以我们不能把'a'放在一个字符。

然后我们再尝试把'b'放在第一个字符。这时剩余的S'是"bbac"，我们知道"bbac"至少存在一个解，并且这个解不需要第一个字符一定是'b'(因为如果S'的解需要第一个字符一定是某个ch，那么S=S'+ch一定INVALID，大家可以仔细想想）。所以我们可以安全的令第一个字符是'b'，一定是字典序最小的选择。

同样的贪心策略处理3个字符后之后，我们就会得到前3个字符是："bab"，这时余下的字符是"bc"。注意由于前一个字符是'b'，所以此时字典序的第一选择'b'不能被选（尽管出去'b'之后剩余字符仍 然有解），所以第四个字符选'c'。

最终我们得到答案："babcb"。

本题的关键就是每一个字符选择时，都需要判断剩余字符有没有解。由于只有'a'-'z'26个字母，判断有没有解可以认为是O(26)=O(1)即常数复杂度的。所以总复杂度是O(|S|)。
*/


#include <vector>
#include <string>
#include <iostream>
using namespace std;

bool check(vector<int>& count, int len) {
    for (auto i : count) {
        if (i > (len + 1) / 2)
            return false;
    }
    return true;

}
int main() {
    string s;
    cin >> s;
    vector<int> count(26,0);
    for (auto c : s) {
        auto index = c - 'a';
        ++count[index];
    }

    auto len = s.size();
    if (!check(count, len)) {
        cout << "INVALID" << endl;
        return 0;
    }

    int pre_i = 27;
    int early_break = 0;
    string result = "";
    while (len > 0) {
        int ok = 0;
        for (int i = 0; i < 26; ++i) {
            if (i == pre_i || count[i] == 0) continue;
            --count[i];
            if (!check(count, len - 1)) {
                ++count[i];
                continue;
            }
            else {
                pre_i = i;
                ok = 1;
                result += ('a' + i);
                break;
            }
        }
        if (ok) --len;
        else {
            early_break = 1;
            break;
        }
    }

    if (early_break)
        cout << "INVALID" << endl;
    else
        cout << result << endl;
}