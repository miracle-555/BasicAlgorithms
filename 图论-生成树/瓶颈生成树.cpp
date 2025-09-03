/*
瓶颈生成树 + 并查集
n和m分别是点和边的个数
u, v, w指的是点u和点v之间有一条权值是w的边
输出瓶颈生成树的瓶颈, 即最小生成树中权值最大的边
任意最小生成树（MST）也是瓶颈生成树, 但瓶颈生成树不一定是最小生成树（除非边值互异）
*/

/*
示例输入:
4 5
1 2 3
1 3 5
2 4 2
4 3 2
4 1 4

示例输出:
3
*/

#include <iostream>
#include <vector>
#include <utility>
#include <functional>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

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
            ans = max(ans, w);   // 注意这里
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