/*
双哈希
有s1和s2两个字符串, 求s1在s2中出现的次数
字符串长度都不超过10**6
*/

/*
示例输入:
cdd
cddccdccdddccdd

示例输出:
3
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const ll N = 1000000;

const ll sed1 = 23; 
const ll MOD1 = 1000000007;
const ll sed2 = 233;
const ll MOD2 = 998244353;

ll hash1[N + 1], hash2[N + 1];  // 越左幂次越高, 避免计算乘法逆元
ll qp1[N + 1], qp2[N + 1];

void init(string s){  // hash[i]表示string[0:i]的哈希值, 闭区间
    hash1[0] = s[0] % MOD1;
    qp1[0] = 1;
    hash2[0] = s[0] % MOD2;
    qp2[0] = 1;
    for (ll i = 1; i < s.size(); i++){
        hash1[i] = (hash1[i - 1] * sed1 % MOD1 + s[i]) % MOD1;
        qp1[i] = qp1[i - 1] * sed1 % MOD1;
        hash2[i] = (hash2[i - 1] * sed2 % MOD2 + s[i]) % MOD2;
        qp2[i] = qp2[i - 1] * sed2 % MOD2;
    }
}

ll get_hash1(ll l, ll r){  // func_hash(l, r)表示string[l:r]的哈希值, 闭区间
    if (l == 0) return hash1[r];
    return ((hash1[r] - hash1[l - 1] * qp1[r - l + 1]) % MOD1 + MOD1) % MOD1;    // 避免出现负数
}

ll get_hash2(ll l, ll r){ 
    if (l == 0) return hash2[r];
    return ((hash2[r] - hash2[l - 1] * qp2[r - l + 1]) % MOD2 + MOD2) % MOD2;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string s1, s2;
    cin >> s1 >> s2;

    init(s2);   // 记得初始化

    // 计算s1的俩hash值
    ll ha1 = s1[0] % MOD1, ha2 = s1[0] % MOD2;
    for (ll i = 1; i < s1.size(); i++){
        ha1 = (ha1 * sed1 % MOD1 + s1[i]) % MOD1; 
        ha2 = (ha2 * sed2 % MOD2 + s1[i]) % MOD2; 
    } 

    ll l, r, ans = 0;
    for (l = 0; l <= s2.size() - s1.size(); l++){
        r = l + s1.size() - 1;
        if (get_hash1(l, r) == ha1 && get_hash2(l, r) == ha2) ans++;
    }

    cout << ans;
    return 0;
}