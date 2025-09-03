/*
最小生成树Prim算法 + 优先队列
n和m分别是点和边的个数
u, v, w指的是点u和点v之间有一条权值是w的边
输出最小生成树的权值和
*/

/*
示例输入:
5 6
1 2 3
2 3 4
3 4 5
4 5 6
1 3 2
2 4 1

示例输出:
12
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> graph(n + 1);  // 邻接表
    for (ll i = 0; i < m; i++){
        ll u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    ll ans = 0;
    ll cnt = 0;
    int vis[n + 1] = {0};   // 记录已经访问的点
    priority_queue<pair<ll, ll>> q;  // first为距离，second为点
    q.push({0, 1});
    while (!q.empty()){
        auto [tem, p] = q.top(); q.pop();
        if (vis[p]) continue;

        ans -= tem;
        vis[p] = 1;
        for (auto [u, w]: graph[p]){
            if (!vis[u]) q.push({-w, u});
        }
        cnt++;
        if (cnt == n) break;
    }
    
    if (cnt != n){
        cout << -1;
        return 0;
    }
    cout << ans;
    return 0;
}