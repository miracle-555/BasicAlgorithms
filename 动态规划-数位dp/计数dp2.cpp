/*
计数dp
输出[a, b]之间的数字中满足各个相邻位数之间差都大于等于2的个数
个位数也计入
*/

/*
示例输入:
3 14

示例输出:
9
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll a, b;
    cin >> a >> b;

    function<ll(ll)> DP = [&](ll x){
        if (x <= 9) return x;
        vector<ll> s;
        while (x){
            s.push_back(x % 10);
            x /= 10;
        }
        s.push_back(0);
        reverse(s.begin(), s.end());
    
        ll width = s.size();    // 数位+1
        ll dp[width][10][2];   // dp[i][j][k]: 第i位, 当前位为j, k为是否触顶
        memset(dp, 0, sizeof(dp));
        // 初始化
        for (ll j = 1; j < s[1]; j++) dp[1][j][0] = 1;  // 跳过j=0
        dp[1][s[1]][1] = 1;
        
        for (ll i = 2; i < width; i++)
            for (ll j = 0; j <= 9; j++)
                for (ll num = 0; num <= 9; num++)
                    if (abs(j - num) >= 2){
                        dp[i][j][0] += dp[i - 1][num][0];
                        if (j < s[i]) dp[i][j][0] += dp[i - 1][num][1];
                        if (j == s[i]) dp[i][j][1] += dp[i - 1][num][1];
                    }
            
        ll ans = 0;
        for (ll j = 0; j <= 9; j++)
            for (ll k = 0; k <= 1; k++)
                ans += dp[width - 1][j][k];
        return ans + DP((ll)pow(10, width - 2) - 1);   // 递归处理前导0
    };

    cout << DP(b) - DP(a - 1);
    return 0;
}