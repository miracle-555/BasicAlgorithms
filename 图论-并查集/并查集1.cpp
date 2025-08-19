/*
并查集
N表示列的个数(1~N), M表示操作的个数
起始每列都只有一个节点, 节点的值为列的编号
opt = 1表示合并两个列, 将x所在列放在y所在列之后
opt = 2表示输出x和y俩节点之间节点的个数
*/

/*
示例输入:
3 5
2 1 2
1 2 1 
2 1 2
1 1 3
2 2 3

示例输出:
-1
0
1
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll N, M;
    cin >> N >> M;
    vector<ll> rot(N + 1);  // 所在列最前面的元素
    for (ll i = 1; i <= N; i++) rot[i] = i;
    vector<ll> dep(N + 1, 0);  // i距rot[i]的距离
    vector<ll> size(N + 1, 1);  // 所在列的长度, 只用维护首个的

    auto merge = [&](ll u, ll v){    // 将u所在列放在v所在列之后
        ll ru = rot[u], rv = rot[v];    // ru都指的是变化前的
        rot[ru] = rv;
        dep[ru] = size[rv];   // 方便后面更新
        size[rv] += size[ru];
    };
    
    function<ll(ll)> find = [&](ll u){   // 找更新后的rot, 且顺便更新中间的元素
        if (u == rot[u]) return u;
        ll ru = rot[u];
        rot[u] = find(rot[u]);        // 优先更新避免出问题; auto不能递归, 只能function
        dep[u] += dep[ru];   // 需要更新的部分加的是size, 不需要更新的部分加的是0
        return rot[u];
    };

    while (M--){
        ll opt, x, y;
        cin >> opt >> x >> y;
        find(x); find(y);    // 记得遇到就更新, 因为提前更新很难确保每个元素都被更新
        if (opt == 1){
            if (rot[x] != rot[y]) merge(x, y);
        }
        else{
            if (rot[x] == rot[y]){
                cout << max(abs(dep[x] - dep[y]) - 1, 0LL) << "\n";   // 注意这里的max
            }
            else cout << -1 << "\n";
        }
    }
    
    return 0;
}