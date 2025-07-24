/*
背包的存在性问题
n表示数据个数
把数据分成两类，使得这两类的各自和的乘积最大
*/

/*
示例输入:
40
5160 9191 6410 4657 7492 1531 8854 1253 4520 9231
1266 4801 3484 4323 5070 1789 2744 5959 9426 4433
4404 5291 2470 8533 7608 2935 8922 5273 8364 8819
7374 8077 5336 8495 5602 6553 3548 5267 9150 3309

示例输出:
12873625444
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll n;   // 输入
    cin >> n;
    vector<ll> v(n);
    for (ll& num: v) cin >> num;

    ll s = accumulate(v.begin(), v.end(), 0LL);  // 0LL防止溢出
    auto ave = 1.0 * s / 2;
    ll N = s + 1;

    vector<ll> dp(N, 0);   // 找是否存在
    dp[0] = 1;
    for (ll i = 0; i < n; i++){
        for (ll j = N - 1; j >= v[i]; j--) dp[j] = dp[j] | dp[j - v[i]];
    }

    ll ans = 0;    // 找答案
    for (ll num = 0; num < N; num++){
        if (ans >= ave) break;   // 可能刚好是均值
        if (dp[num] == 1) ans = num;
    }
    
    cout << ans * (s - ans);   // 输出
    return 0;
}
