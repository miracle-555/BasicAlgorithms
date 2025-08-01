/*
LCA
N代表树的大小
u和v表示N-1条边的两个节点
Q表示询问次数
a和b表示一次对最近公共祖先的询问
*/

/*
示例输入:
5
1 2
1 3
2 4
2 5
3
4 5
3 4
3 5

示例输出:
2
1
1
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll N, u, v;
    cin >> N;
    vector<ll> tree[N + 1];
    
    ll d[N + 1] = {0};   // 记录深度, 默认d[0] = 0
    d[1] = 1;
    ll width = (ll)log2(N) + 4;  // +4可以保证不出问题
    ll fa[N + 1][width];  // fa[i][j]表示i向上求父节点2**j次后的节点
    memset(fa, 0, sizeof(fa));

    ll k = N - 1;   // 构建邻接表, 而且前者不一定是后者的父节点
    while (k--){
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    queue<ll> q;   // dfs构建树上节点之间的关系
    q.push(1);
    while (!q.empty()){
        u = q.front(); q.pop();
        for (ll v: tree[u]){
            if (d[v] == 0){     // 还没有找过深度
                d[v] = d[u] + 1;
                fa[v][0] = u;
                q.push(v);
            }
        }
    }

    for (ll j = 1; j < width; j++){   // 先j后i是因为递推公式中推理到j时要求知道每一个（因为都有可能）的fa[i][j - 1]
        for (ll i = 1; i <= N; i++){
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
        }
    }
  
    ll Q, a, b;
    cin >> Q;
    while (Q--){
        cin >> a >> b;
        if (d[a] < d[b]) swap(a, b);

        ll base = width - 1;
        while (base >= 0){   // 两处都以base>=0为判断条件, 代码好写
            if (d[fa[a][base]] >= d[b]) a = fa[a][base];
            base--;
        }

        if (a == b){
            cout << a << "\n";
            continue;
        }

        base = width - 1;
        while (base >= 0){
            if (fa[a][base] != fa[b][base]){
                a = fa[a][base];
                b = fa[b][base];
            }
            base--;
        }
        cout << fa[a][0] << "\n";
    }

    return 0;
}