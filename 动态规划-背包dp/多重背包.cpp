/*
多重背包 + 完全背包
N和V分别表示物品数量和背包最大容量
w、v、s分别表示单个物品的体积、价值、个数
s = 0时表示有无数个
求最大可装进背包内的价值
*/

/*
示例输入:
3 66
3 3 0
2 4 3
5 6 5

示例输出:
75
*/

#include <iostream>
#include <vector>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N, V, w, v, s;
    cin >> N >> V;
    vector<ll> dp(V + 1, 0);

    for (ll i = 0; i < N; i++){
        cin >> w >> v >> s;
        if (s == 0) s = V / w + 1;   // 无穷个可以如此转化
        ll base = 1;     // 引入基数，对s二进制分解
        while (s >= base){
            for (ll j = V; j >= 0; j--) if (j >= base * w) dp[j] = max(dp[j], dp[j - base * w] + base * v);
            s -= base;
            base <<= 1;
        }
        if (s > 0) for (ll j = V; j >= 0; j--) if (j >= s * w) dp[j] = max(dp[j], dp[j - s * w] + s * v);
    }
    
    cout << dp[V];
    return 0;
}