/*
线性dp
一共n个数字构成数组a[n], 对其分成k组, 每组必须连续且非空
这k组不相交且并集为全集
求max{sum(p[j] * sum[j])}, j = 1, 2, ..., k
其中p[j]为给定的权重, sum[j]为第j组中数字的和  
*/

/*
示例输入:
5 2
1 -2 4 3 -9
-1 4

示例输出:
-7
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    ll n, k;
    cin >> n >> k;
    ll a[n], p[k];
    for (ll i = 0; i < n; i++) cin >> a[i];
    for (ll i = 0; i < k; i++) cin >> p[i];

    ll dp[n][k];  // dp[i][j]表示i元素放进j内计算后最大的和值
    memset(dp, -0x7f, sizeof(dp));

    // 构建dp数组, 其实可以一次大循环就解决, 只是为了减少判断就分开了
    dp[0][0] = a[0] * p[0];
    for (ll i = 1; i < n; i++)
        dp[i][0] = dp[i - 1][0] + a[i] * p[0];
    for (ll i = 1; i < n; i++)
        for (ll j = 1; j < k; j++)
            dp[i][j] = max(dp[i - 1][j - 1], dp[i - 1][j]) + a[i] * p[j];  // 要么和前面那个放一起, 要么单独新开一个
    
    cout << dp[n - 1][k - 1];
    return 0; 
}