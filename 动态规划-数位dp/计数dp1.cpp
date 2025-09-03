/*
计数dp
输出1到n之间所有数对应二进制含'1'恰好为K个的个数
*/

/*
示例输入:
7 2

示例输出:
3
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, K;
    cin >> n >> K;

    vector<ll> s;
    while (n){
        s.push_back(n & 1);
        n >>= 1;
    }
    s.push_back(0);
    reverse(s.begin(), s.end());

    ll width = s.size();
    ll dp[width][K + 1][2];
    memset(dp, 0, sizeof(dp));
    dp[0][0][1] = 1;

    for (ll i = 1; i < width; i++)
        for (ll j = 0; j <= K; j++)
            for (ll num = 0; num <= 1; num++){
                if (num == 1 && j >= 1){
                    dp[i][j][0] += dp[i - 1][j - 1][0];
                    if (num < s[i]) dp[i][j][0] += dp[i - 1][j - 1][1];
                    if (num == s[i]) dp[i][j][1] += dp[i - 1][j - 1][1];
                }
                if (num == 0){    // 直接用else会出错
                    dp[i][j][0] += dp[i - 1][j][0];
                    if (num < s[i]) dp[i][j][0] += dp[i - 1][j][1];
                    if (num == s[i]) dp[i][j][1] += dp[i - 1][j][1];  
                }
            }
            
    cout << dp[width - 1][K][0] + dp[width - 1][K][1];
    return 0;
}