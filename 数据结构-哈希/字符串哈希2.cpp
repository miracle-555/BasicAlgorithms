/*
双哈希 + 二分答案
S和T两个字符串, 求T的前缀在S中出现的最长长度
字符串长度都不超过10**6
*/

/*
示例输入:
aabba
abb

示例输出:
3
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const ll N = 1000000;

const ll sed1 = 23, sed2 = 233;
const ll MOD1 = 1000000007, MOD2 = 998244353;

ll hash1[N + 1], hash2[N + 1], qp1[N + 1], qp2[N + 1];

void init(string s){
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

ll get_hash1(ll l, ll r){
    if (l == 0) return hash1[r];
    return ((hash1[r] - hash1[l - 1] * qp1[r - l + 1]) % MOD1 + MOD1) % MOD1;
}

ll get_hash2(ll l, ll r){
    if (l == 0) return hash2[r];
    return ((hash2[r] - hash2[l - 1] * qp2[r - l + 1]) % MOD2 + MOD2) % MOD2;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    string S, T;
    cin >> S >> T;
    
    init(S);

    // 计算T串前缀的hash值
    ll hashT1[T.size()], hashT2[T.size()];
    hashT1[0] = T[0] % MOD1, hashT2[0] = T[0] % MOD2;
    for (ll i = 1; i < T.size(); i++){
        hashT1[i] = (hashT1[i - 1] * sed1 % MOD1 + T[i]) % MOD1;
        hashT2[i] = (hashT2[i - 1] * sed2 % MOD2 + T[i]) % MOD2;
    }

    // is_ok函数
    function<int(ll)> is_ok = [&](ll len){
        ll l, r;
        for (l = 0; l <= S.size() - len; l++){
            r = l + len - 1;
            if (get_hash1(l, r) == hashT1[len - 1] && get_hash2(l, r) == hashT2[len - 1]){
                return 1;
            }
        }
        return 0;
    };   // 别忘了分号

    // 二分答案
    ll l = 1, r = T.size(), mid;
    if (is_ok(T.size())){
        cout << T.size();
        return 0;
    }

    while (l < r){
        mid = (l + r) / 2;  // 越大越不可以
        if (is_ok(mid)) l = mid + 1;
        else r = mid;
    }

    cout << l - 1;
    return 0;
}