/*
拓扑排序
n表示有n个节点(1~n)
同时有n个边, 表明有且只有一个环
按从小到大输出环上的节点值
*/

/*
示例输入:
5
1 2
3 1
2 4
2 5
5 3

示例输出:
1 2 3 5
*/

#include <iostream>
#include <vector>
#include <queue>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n;
    cin >> n;
    vector<vector<ll>> v(n + 1);
    vector<ll> deg(n + 1, 0);
    queue<ll> q;

    for (ll i = 0; i < n; i++){
        ll a, b;
        cin >> a >> b;
        v[a].push_back(b);
        v[b].push_back(a);
        deg[a]++;   // 无向图, 记录节点的度
        deg[b]++; 
    }

    for (ll i = 1; i <= n; i++){
        if (deg[i] == 1) q.push(i);
    }

    while (!q.empty()){
        ll tem = q.front(); q.pop();
        for (ll u: v[tem]){
            deg[u]--;   // 一定不会再次触发
            if (deg[u] == 1) q.push(u);
        }
    }

    for (ll i = 1; i <= n; i++){
        if (deg[i] == 2) cout << i << " ";  // 
    }
    return 0;
}