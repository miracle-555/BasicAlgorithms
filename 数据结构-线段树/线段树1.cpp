/*
线段树
数组N个元素, q次处理
opt为1表示将位置a增加b
opt为2表示输出[a, b]的和
输入端都是从1开始
*/

/*
示例输入:
6
4 5 6 2 1 3
4
1 3 5
2 1 4
1 1 9
2 2 6

示例输出: 
22
22
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    // 输入
    ll N, q, opt, a, b;
    cin >> N;
    vector<ll> v(N + 1);
    for (ll i = 1; i <= N; i++) cin >> v[i];  // 1-based
    cin >> q;

    // 线段树初始化
    vector<ll> val(4 * N);   // 目标值, val[id]表示第id个区间[l, r]的目标值
    
    // 线段树的对应函数
    function<void(ll, ll, ll)> build = [&](ll id, ll l, ll r){
        if (l == r){
            val[id] = v[l];
            return;
        }

        ll mid = ((l + r) >> 1);
        build(id << 1, l, mid);
        build((id << 1) | 1, mid + 1, r);
        val[id] = val[id << 1] + val[(id << 1) | 1];
    };
    build(1, 1, N);  // 初始化别忘记了

    function<ll(ll, ll, ll, ll, ll)> get = [&](ll a, ll b, ll id, ll l, ll r){   // 前两个变量不变, 减少代码的复杂程度
        if (b < l || a > r) return 0LL;
        if (a <= l && b >= r){
            return val[id];
        }
        
        ll mid = ((l + r) >> 1);
        return get(a, b, id << 1, l, mid) + get(a, b, (id << 1) | 1, mid + 1, r);
    };

    function<void(ll, ll, ll, ll, ll)> upd = [&](ll a, ll b, ll id, ll l, ll r){
        val[id] += b;
        if (l == r) return;
        
        ll mid = ((l + r) >> 1);
        if (a <= mid) upd(a, b, id << 1, l, mid);
        else upd(a, b, (id << 1) | 1, mid + 1, r);
    };
    
    // q次询问
    while (q--){
        cin >> opt >> a >> b;
        if (opt == 1){
            upd(a, b, 1, 1, N);
        }
        else{
            cout << get(a, b, 1, 1, N) << "\n";
        }
    }
    return 0;
}