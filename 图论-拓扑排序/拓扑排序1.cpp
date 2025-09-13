/*
拓扑排序
n表示有n个节点(1~n), m表示有m组关系
每组关系表示a必须在b的左边
排成横着一列
输出字典序最小的方案, 没有则返回-1
*/

/*
示例输入:
4 2
1 2
3 4

示例输出:
1 2 3 4
*/

#include <iostream>
#include <vector>
#include <queue>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, m;
    cin >> n >> m;
    vector<vector<ll>> v(n + 1);
    vector<ll> deg(n + 1, 0);
    priority_queue<ll> q;  // 是大根堆, 别忘了负输入
    vector<ll> ans;

    while (m--){
        ll a, b;
        cin >> a >> b;
        v[a].push_back(b);
        deg[b]++;   // 有向图, 记录节点的入度
    }

    for (ll i = 1; i <= n; i++){
        if (!deg[i]) q.push(-i);
    }

    while (!q.empty()){
        ll tem = -q.top(); q.pop();
        ans.push_back(tem);
        for (ll u: v[tem]){
            deg[u]--;
            if (!deg[u]) q.push(-u);
        }
    }

    if (ans.size() < n) cout << -1;
    else for (ll tem: ans) cout << tem << " ";
    return 0;
}