/*
带权并查集
N表示节点个数, q表示边数
将节点分为两个小组, 俩小组相互无边连接, 俩小组内部都存在边连接, 输出最大权值可能的最小值
不在q组中的边权都视为0
细节: 在并查集中同属于一个集合并非表示分到一个小组, 而表示在当前的情况下存在相互约束条件
*/

/*
示例输入:
4 6
1 4 2534
2 3 3512
1 2 28351
1 3 6618
2 4 1805
3 4 12884

示例输出:
3512
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ll N, q;
    cin >> N >> q;
    vector<ll> rot(N + 1);
    for (ll i = 1; i <= N; i++) rot[i] = i;
    vector<ll> w(N + 1, 0);   // 权值, w[i]表示i与rot[i]是否属于同一个监狱（1表示非）
    vector<pair<ll, pair<ll, ll>>> edge(q);
    for (ll i = 0; i < q; i++){
        ll a, b, k;
        cin >> a >> b >> k;
        edge[i].first = -k;
        edge[i].second = {a, b};
    }

    auto merge = [&](ll u, ll v){
        ll ru = rot[u], rv = rot[v];
        rot[ru] = rv;
        w[ru] = 1 ^ w[u] ^ w[v];  // 异或, 1表示u和v之间, w[ru]表示ru与rot[ru]=rv之间, w[u]表示u与ru之间, w[v]表示v与rv之间
    };   // 记得分号

    function<ll(ll)> find = [&](ll u){
        if (u == rot[u]) return u;
        ll ru = rot[u];
        rot[u] = find(rot[u]);
        w[u] ^= w[ru];    // w[ru]指的是ru与rot[ru]=rot[u]之间, w[u]变化前表示u与ru之间, 变化后表示u与rot[u]之间
        return rot[u];
    };

    sort(edge.begin(), edge.end());
    for (auto [k, tem]: edge){
        ll a = tem.first, b = tem.second;
        find(a); find(b);
        if (rot[a] == rot[b]){
            if (w[a] == w[b]){
                cout << -k;
                return 0;
            }
        }
        else merge(a, b);
    }

    cout << 0;
    return 0;
}