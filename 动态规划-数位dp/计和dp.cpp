/*
计和dp
输出[l, r]中含（必须连续）"2022"子串的数的和
*/

/*
示例输入:
1 20000

示例输出:
14044
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

    ll l, r;
    cin >> l >> r;
    
    auto opt = [&](ll pre, ll k){
        if (pre == 4) return 4LL;
        if (k == 2 && pre != 1) return pre + 1;
        if (k == 2) return 1LL;
        if ((pre == 1 || pre == 3) && k == 0) return 2LL;
        return 0LL;
    };

    function<ll(ll)> DP = [&](ll x) -> ll {
        if (x <= 2021) return 0;
        vector<ll> s;
        while (x){
            s.push_back(x % 10);
            x /= 10;
        }
        s.push_back(0);
        reverse(s.begin(), s.end());
    
        ll width = s.size();
        ll dp[width][5][2];
        memset(dp, 0, sizeof(dp));
        ll ans[width][5][2];
        memset(ans, 0, sizeof(ans));
        dp[0][0][1] = 1;
        
        for (ll i = 1; i < width; i++)
            for (ll j = 0; j <= 4; j++)
                for (ll num = 0; num <= 9; num++){
                    ll tem = opt(j, num);
                    dp[i][tem][0] += dp[i - 1][j][0];
                    ans[i][tem][0] += ans[i - 1][j][0] * 10 + num * dp[i - 1][j][0];
                    if (num < s[i]){
                        dp[i][tem][0] += dp[i - 1][j][1];
                        ans[i][tem][0] += ans[i - 1][j][1] * 10 + num * dp[i - 1][j][1];
                    }
                    if (num == s[i]){
                        dp[i][tem][1] += dp[i - 1][j][1];
                        ans[i][tem][1] += ans[i - 1][j][1] * 10 + num * dp[i - 1][j][1];
                    }
                }

        return ans[width - 1][4][0] + ans[width - 1][4][1];
    };

    cout << DP(r) - DP(l - 1);
    return 0;
}