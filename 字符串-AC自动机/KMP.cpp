/*
KMP算法
输入s1和s2两个字符串
隔行输出s2在s1中出现的位置(首字符)
另起一行隔空格输出next数组, next[i]表示s2[0:i]闭区间上的最长的“非自身的”相同前缀和后缀长度
（本题都是0-based）
*/

/*
示例输入:
ABABABC
ABA

示例输出:
0
2
0 0 1
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string s1, s2;
    cin >> s1 >> s2;

    vector<int> next(s2.length());

    auto init = [&]() {
        int i = 1, j = 0;
        next[0] = 0;
        while (i < s2.length()) {
            if (s2[i] == s2[j]) {
                next[i] = j + 1;  // 表示符合的个数
                i++; j++;
            }
            else {
                if (j == 0) i++;
                else j = next[j - 1];  // 回退, -1是因为0-based
            }
        }
    };
    init();

    auto KMP = [&]() {
        int i = 0, j = 0;
        while (i < s1.length()) {
            if (s1[i] == s2[j]) {
                i++; j++;
            }
            else {
                if (j == 0) i++;
                else j = next[j - 1];
            }
            if (j == s2.length()) {
                cout << i - j << "\n";
                j = next[j - 1];
            }
        }
    };
    KMP();
    
    for (auto x: next) cout << x << " ";
    return 0;
}
