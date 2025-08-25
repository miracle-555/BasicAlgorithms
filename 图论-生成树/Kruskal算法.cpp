/*
最小生成树Kruskal算法 + 并查集
n和m分别是点和边的个数
u, v, w指的是点u和点v之间有一条权值是w的边
输出最小生成树的权值和
*/

/*
示例输入:
4 5
1 2 2
1 3 2
1 4 3
2 3 4
3 4 3

示例输出:
7
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<pair<ll, pair<ll, ll>>> edges(m);
    for (ll i = 0; i < m; i++){
        ll u, v, w;
        cin >> u >> v >> w;
        edges[i] = {w, {u, v}};
    }
    sort(edges.begin(), edges.end());
    
    ll fa[n + 1];
    for (ll i = 1; i <= n; i++) fa[i] = i;
    function<ll(ll)> find = [&](ll u){
        if (u == fa[u]) return u;
        fa[u] = find(fa[u]);
        return fa[u]; 
    };
    auto merge = [&](ll u, ll v){
        fa[fa[u]] = fa[v];
    };

    ll ans = 0;
    ll cnt = 0;
    for (auto [w, tem]: edges){
        ll u = tem.first, v = tem.second;
        find(u); find(v);
        if (fa[u] != fa[v]){
            ans += w;
            cnt++;
            merge(u, v);
        }
        if (cnt == n - 1) break;
    }

    if (cnt != n - 1){
        cout << -1;
        return 0;
    }
    cout << ans;
    return 0;
}