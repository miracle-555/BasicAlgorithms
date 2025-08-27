/*
状压dp + 最短哈密顿路径
n是点的个数, 后面n个数是每个点的三维坐标
三维空间中任意选择起点, 找到一条路径经过每个点恰好一次，不需要回到起点
输出最短路径的长度, 保留两位小数
*/

/*
示例输入:
3
4 3 3
2 2 3
3 1 1

示例输出:
4.69
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll n;
    cin >> n;
    vector<vector<ll>> pos(n, vector<ll>(3));
    double dist[n][n];
    memset(dist, 0, sizeof(dist));
    for (ll i = 0; i < n; i++){
        cin >> pos[i][0] >> pos[i][1] >> pos[i][2];
    }

    for (ll i = 0; i < n - 1; i++){
        for (ll j = i + 1; j < n; j++){
            ll tem = 0;
            for (ll k = 0; k <= 2; k++)
                tem += pow(pos[i][k] - pos[j][k], 2);
            dist[i][j] = pow(tem, 0.5);
            dist[j][i] = dist[i][j];
        }
    }

    vector<vector<double>> dp(1 << n, vector<double>(n, INFINITY));
    for (ll j = 0; j < n; j++) dp[1 << j][j] = 0.0;  // 初始化记得别搞错了
    for (ll i = 1; i < (1 << n); i++){
        for (ll j = 0; j < n; j++){
            if (dp[i][j] == INFINITY) continue;   // 不合法情况剪去
            for (ll k = 0; k < n; k++){
                if (i & (1 << k)) continue;    // 重复情况剪去
                ll tem = i | (1 << k);
                dp[tem][k] = min(dp[tem][k], dp[i][j] + dist[j][k]);
            }
        }
    }        

    double ans = INFINITY;
    for (ll j = 0; j < n; j++) ans = min(ans, dp[(1 << n) - 1][j]);
    cout << fixed << setprecision(2) << ans;
    return 0;
}