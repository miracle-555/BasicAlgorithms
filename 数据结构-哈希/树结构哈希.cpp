/*
树链双哈希
n和m为两个树的节点个数, 编号各自从1到n或者m
第2行是第一棵树对应节点的权值
第3行是第二棵树对应节点的权值
再往下n-1行是树1的边
再往下m-1行是树2的边
求两棵树由权值构成的最长的公共链形前缀的长度
*/

/*
示例输入:
5 4
10 20 30 40 50
10 40 20 30
1 2
1 3
2 4
3 5
1 2
1 3
3 4

示例输出:
2
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const ll sed1 = 23, sed2 = 233;
const ll MOD1 = 1000000007, MOD2 = 998244353;

ll ans = 0;   // 直接全局定义ans, 方便dfs在全局中编写
set<pair<ll, ll>> hashes;

void dfs1(ll u, ll fa, ll ha1, ll ha2, vector<ll>* tree, ll* r){
    ha1 = (ha1 * sed1 % MOD1 + r[u]) % MOD1;
    ha2 = (ha2 * sed2 % MOD2 + r[u]) % MOD2;
    hashes.insert({ha1, ha2});
    for (ll v: tree[u]){
        if (v != fa){
            dfs1(v, u, ha1, ha2, tree, r);
        }
    }
}

void dfs2(ll u, ll fa, ll ha1, ll ha2, ll len, vector<ll>* tree, ll* r){
    ha1 = (ha1 * sed1 % MOD1 + r[u]) % MOD1;
    ha2 = (ha2 * sed2 % MOD2 + r[u]) % MOD2;
    if (hashes.find({ha1, ha2}) != hashes.end()){
        ans = max(ans, len);
    }
    for (ll v: tree[u]){
        if (v != fa){
            dfs2(v, u, ha1, ha2, len + 1, tree, r);
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll n, m, u, v;
    cin >> n >> m;

    ll r1[n + 1], r2[m + 1];  // 权值
    vector<ll> tree1[n + 1], tree2[m + 1];
    for (ll i = 1; i <= n; i++) cin >> r1[i];
    for (ll i = 1; i <= m; i++) cin >> r2[i];

    for (ll i = 1; i < n; i++){
        cin >> u >> v;
        tree1[u].push_back(v);
        tree1[v].push_back(u);
    }
    for (ll i = 1; i < m; i++){
        cin >> u >> v;
        tree2[u].push_back(v);
        tree2[v].push_back(u);
    }  

    dfs1(1, 0, 0, 0, tree1, r1);
    dfs2(1, 0, 0, 0, 1, tree2, r2);
    cout << ans;
    return 0;
}