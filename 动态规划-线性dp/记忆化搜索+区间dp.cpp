/*
记忆化搜索 + 区间dp
给一个数字s, 任意选择该数字构成的字符串的一个连续子区间
使得该子区间从l到r翻转后, 填充回原来的数字, 严格比初始s小
问有多少种选择方案, 方案不同当且仅当l和r都不同
*/

/*
示例输入:
210102

示例输出:
8
*/

#include <iostream>
#include <vector>
#include <functional>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    string s;
    cin >> s;
    ll n = s.size();  // 因为是直接比较大小, 所以没必要转化为数字
    vector<vector<int>> dp(n, vector<int>(n, -1));      // -1表示不合法, 0表示不行, 1表示可以
                                                        //  不用变长数组(即dp[n][n])是因为其无法被lambda表达式捕获
    function<int(ll, ll)> DP = [&](ll l, ll r){   // 区间最优可以由其子区间更优得到
        if (l >= r) return 0;   // 前面都相等自然不行; 而且比直接去dp数组中调用快
        if (dp[l][r] >= 0) return dp[l][r];

        if (s[l] > s[r]) return 1;
        if (s[l] < s[r]) return 0;
        return DP(l + 1, r - 1);  // 相等的情况
    };

    ll ans = 0;
    for (ll i = 0; i < n - 1; i++)
        for (ll j = i + 1; j <= n - 1; j++)  // 有部分可以不用讨论
            if ((dp[i][j] = DP(i, j)) == 1) ans++;
    cout << ans;
    return 0;
}