/*
欧拉降幂 + 快速幂
输入n和m
求n的exp次幂对MOD取模后的值
其中, exp是1到m的所有正整数的累乘
*/

/*
示例输入:
2 3

示例输出:
64
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const ll MOD = 1000000007;

ll qpow(ll a, ll exp, ll mod){   // function无法弄ll的, 故还是放全局中
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

    ll n, m, exp = 1;
    cin >> n >> m;
    ll phi_MOD = MOD - 1;      // 素数, phi(MOD) = MOD - 1

    while (m){    // 欧拉降幂
        exp = exp * m % phi_MOD;    
        m--;
    }

    cout << qpow(n, exp, MOD);
    return 0;
}