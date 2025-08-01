/*
LCA + dfs
N代表树的大小, Q表示总路径的条数
u和v表示N-1条边的两个节点
a和b表示一次路径
最后返回一条路的编号, 使得去掉这条路径后, 前面Q条路都会断掉
无答案返回-1, 多答案返回最大的编号
*/

/*
示例输入:
6 2
1 2
2 3
4 3
2 5
6 5
3 6
4 5

示例输出:
4
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll N, M, u, v;
    cin >> N >> M;
    vector<pair<ll, ll>> tree[N + 1];   // 配了个元素做位置
    ll c[N + 1];  // 以点代边, c[i]表示的意思是边(*, i)的编号c[i]（子节点一定1对1）

    ll d[N + 1] = {0};  // 深度
    d[1] = 1;
    ll width = (ll)log2(N) + 4;
    ll fa[N + 1][width];
    memset(fa, 0, sizeof(fa));

    ll k = N - 1;   // 构建邻接表
    while (k--){
        cin >> u >> v;
        tree[u].push_back({v, N - k - 1});
        tree[v].push_back({u, N - k - 1});
    }

    queue<ll> q;   // 用队列构建树
    q.push(1);
    while (!q.empty()){
        u = q.front(); q.pop();
        for (auto [v, id]: tree[u]){
            if (d[v] == 0){
                d[v] = d[u] + 1;
                fa[v][0] = u;
                c[v] = id;   // 边(*, v)的编号  
                q.push(v);
            }
        }
    }

    for (ll j = 1; j < width; j++){   // 跟ST表类似
        for (ll i = 1; i <= N; i++){
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
        
    ll s[N + 1] = {0};
    ll a, b, Q = M;
    while (Q--){  
        cin >> a >> b;
        s[a]++; s[b]++;

        if (d[a] < d[b]) swap(a, b);     // LCA部分
        for (ll j = width - 1; j >= 0; j--){
            if (d[fa[a][j]] >= d[b]){
                a = fa[a][j];
            }
        }
        if (a == b){
            s[a] -= 2;
            continue;
        }

        for (ll j = width - 1; j >= 0; j--){
            if (fa[a][j] != fa[b][j]){
                a = fa[a][j];
                b = fa[b][j];
            }
        }
        s[fa[a][0]] -= 2;
    }

    function<void(ll, ll)> dfs = [&](ll u, ll fa){  // 传下来父节点, 保证遍历时不会往后退
        for (auto [v, id]: tree[u]){
            if (v != fa){
                dfs(v, u);   // 先保证前面的节点都计算完毕
                s[u] += s[v];
            }
        }
    };
    dfs(1, 0);

    ll ans = -1;
    for (ll i = 2; i <= N; i++){   // c[i]中的i只在2~N中存在, 以点代边
        if (s[i] == M) ans = max(ans, c[i]);
    }
    cout << ans;
    return 0;
}