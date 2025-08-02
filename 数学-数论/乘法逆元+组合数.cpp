/*
乘法逆元 + 组合数 + 快速幂
q指的是询问次数
求的是C(n,m)对MOD取模后的值
*/

/*
示例输入:
3
3 2
11 7
5 4

示例输出:
3
330
5
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const ll MOD = 1000000007;
const ll N = 10000000;  // n和m不会超过这个值
ll fact[N + 1]; 
ll inv_fact[N + 1];

ll qpow(ll a, ll exp, ll mod){
    a %= mod;
    ll res = 1;
    while (exp){
        if (exp & 1) res = res * a % mod;
        a = a * a % mod;
        exp >>= 1;
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // 初始化阶乘和逆阶乘
    fact[0] = inv_fact[0] = 1;
    for (ll i = 1; i <= N; i++) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[N] = qpow(fact[N], MOD - 2, MOD);   // MOD - 2即为phi(MOD)-1; 再就是这里的底数应该是fact[N], 不是N
    for (ll i = N; i > 1; i--) inv_fact[i - 1] = inv_fact[i] * i % MOD;

    ll q, n, m;
    cin >> q;
    while (q--){
        cin >> n >> m;
        cout << fact[n] * inv_fact[m] % MOD * inv_fact[n - m] % MOD << "\n";
    }

    return 0;
}