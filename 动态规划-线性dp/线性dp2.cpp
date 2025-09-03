/*
线性dp + 前缀和
n, m, q分别代表总可训练天数, 不同训练类型的个数, 以及其间不能用来训练的总天数
ban[t]表示第t天不能用来训练
v[k] = s表示该训练经过连续2 ** k天训练后可以有s的收益, 中断无收益
问最后在总训练天数中最多可以获得多少收益 
亦可以转化为多背包问题
*/

/*
示例输入:
10 3 3
1 4 9
0 3
1 7
2 20

示例输出:
30
*/

#include <iostream>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    ll n, m, q, t, k, s;
    cin >> n >> m >> q;
    ll dp[n + 1] = {0}; 
    ll ban[n + 1] = {0};   // 用来记录是否被ban
    ll v[21] = {0};   // v[k]表示2**k的价值

    while (q--){
        cin >> t;
        ban[t] = 1;
    }
    for (ll i = 1; i <= n; i++) ban[i] += ban[i - 1];
    
    while (m--){
        cin >> k >> s;
        if ((1 << k) <= n) v[k] = max(v[k], s);   // 范围外的丢掉
    }

    for (ll i = 1; i <= n; i++){   // 不能交换先后顺序, 这会导致前序依赖关系未完全处理; 尽量就按逻辑顺序来
        dp[i] = max(dp[i], dp[i - 1]);
        for (k = 0; (1 << k) <= i; k++)     // (1 << k)才是2 ** k, 不是(2 << k)
            if (v[k] > 0 && ban[i] == ban[i - (1 << k)]){  // 注意这里的判断是否被ban的方法
                dp[i] = max(dp[i], dp[i - (1 << k)] + v[k]);
            }
    }

    cout << dp[n];
    return 0;
}