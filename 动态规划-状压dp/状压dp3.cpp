/*
状压dp
n种羊圈, m只羊, v是n种羊圈分别可以框住的最大羊数（必须连续框）
p是m只羊分别跑掉的概率（在不被框住时）, 被框住时一定不能跑掉
一只羊可以被多次框住, 输出跑掉羊数的最小期望, 保留两位小数
*/

/*
示例输入:
3 10
1 2 3
0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0

示例输出:
1.00
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <numeric>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    ll ST = (1 << n);
    vector<ll> v(n);
    for (ll i = 0; i < n; i++) cin >> v[i];
    vector<double> p(m);
    for (ll i = 0; i < m; i++) cin >> p[i];

    if (accumulate(v.begin(), v.end(), 0LL) >= m){
        cout << "0.00";
        return 0;
    }

    vector<vector<double>> dp(m + 1, vector<double>(ST, INFINITY));   // dp[i][s]表示前i只羊被讨论后, 使用羊圈状态为s时的期望
    for (ll j = 0; j < ST; j++) dp[0][j] = 0;
    for (ll i = 1; i <= m; i++){
        for (ll j = 0; j < ST; j++){
            dp[i][j] = min(dp[i - 1][j] + p[i - 1], dp[i][j]);  // 不框住第i只羊
            
            for (ll k = 0; k < n; k++){   // 框住第i只羊    
                if ((j & (1 << k)) == 0) continue;   // 前面记得括号
                ll pre = (j - (1 << k));
                if (i >= v[k]) dp[i][j] = min(dp[i][j], dp[i - v[k]][pre]);
                else dp[i][j] = min(dp[i][j], dp[0][pre]);    
            }
        }
    }

    cout << fixed << setprecision(2) << dp[m][ST - 1];
    return 0;
}