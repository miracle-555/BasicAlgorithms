/*
LCA + 状态压缩
N代表树的大小, Q表示询问次数
再N行: c[i]表示第i个点所含的数字
再Q行: u和v表示N-1条边的两个节点
a和b表示一次询问, 最后输出途径过程上最少的不同数字个数
*/

/*
示例输入:
4 2
1 2 3 1
1 2
1 3
2 4
4 3
1 4

示例输出:
3
2
*/

#include <iostream>
#include <vector>
#include <queue> 
#include <cstring>
#include <cmath>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N, Q, u, v;
    cin >> N >> Q;
    ll c[N + 1];
    for (ll i = 1; i <= N; i++) cin >> c[i];
    vector<ll> tree[N + 1];
    
    ll d[N + 1] = {0};
    d[1] = 1;
    ll width = (ll)log2(N) + 4;
    ll fa[N + 1][width];
    ll s[N + 1][width];  // 表示i到fa[i][j]的所需, 包括i, 但不包括fa[i][j], 方便累积处理
    memset(fa, 0, sizeof(fa));
    memset(s, 0, sizeof(s));

    ll k = N - 1;   // 构建邻接表
    while (k--){
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    queue<ll> q;   // dfs
    q.push(1);
    s[1][0] = 1 << (c[1]- 1);
    while (!q.empty()){
        u = q.front(); q.pop();
        for (ll v: tree[u]){
            if (d[v] == 0){
                d[v] = d[u] + 1;
                fa[v][0] = u;
                s[v][0] = 1 << (c[v] - 1);
                q.push(v);
            }
        }
    }

    for (ll j = 1; j < width; j++){ 
        for (ll i = 1; i <= N; i++){
            fa[i][j] = fa[fa[i][j - 1]][j - 1];
            s[i][j] = s[i][j - 1] | s[fa[i][j - 1]][j - 1];
        }
    }
  
    ll a, b;
    while (Q--){
        cin >> a >> b;
        ll tem = 0, ans = 0;

        if (d[a] < d[b]) swap(a, b);
        ll base = width - 1;
        while (base >= 0){
            if (d[fa[a][base]] >= d[b]){
                tem |= s[a][base];
                a = fa[a][base];
            }
            base--;
        }
        
        if (a == b){
            tem |= s[a][0];
            while (tem){
                if (tem & 1) ans++;
                tem >>= 1;
            }
            cout << ans << "\n";
            break;
        }

        base = width - 1;
        while (base >= 0){
            if (fa[a][base] != fa[b][base]){
                tem |= s[a][base] | s[b][base];
                a = fa[a][base];
                b = fa[b][base];
            }
            base--;
        }

        tem |= s[a][1] | s[b][0];  // 注意别掉了这3个点的
        while (tem){
            if (tem & 1) ans++;
            tem >>= 1; 
        }
        cout << ans << "\n";
    }

    return 0;
}