/*
线段树 + 懒标记
数组N个元素, q次处理
opt为1表示[a, b]增加x
opt为2表示输出[a, b]的和
输入端都是从1开始
*/

/*
示例输入:
5 5
1 2 3 4 5
2 1 2
1 2 3 1
2 1 3
1 1 5 1
2 1 5

示例输出: 
3
8
22
*/

#include <iostream>
#include <vector>
#include <functional>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    // 输入
    ll N, q, opt, a, b;
    cin >> N >> q;
    vector<ll> v(N + 1);
    for (ll i = 1; i <= N; i++) cin >> v[i];  // 1-based

    // 线段树初始化
    vector<ll> val(4 * N);   // 目标值, val[id]表示第id个区间[l, r]的目标值
    vector<ll> lazy(4 * N, 0);   // 懒标记, lazy[id]表示第id个区间[l, r]的懒标记    
    
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

    function<void(ll, ll, ll)> down = [&](ll id, ll l, ll r){
        if (lazy[id]){  // 懒标记下传
            val[id] += lazy[id] * (r - l + 1);
            if (l != r){
                lazy[id << 1] += lazy[id];
                lazy[(id << 1) | 1] += lazy[id];
            }
            lazy[id] = 0;
        }
    };

    function<ll(ll, ll, ll, ll, ll)> get = [&](ll a, ll b, ll id, ll l, ll r){   // 前两个变量不变, 减少代码的复杂程度
        down(id, l, r); 

        if (b < l || a > r) return 0LL;
        if (a <= l && b >= r){
            return val[id];
        }
        
        ll mid = ((l + r) >> 1);
        return get(a, b, id << 1, l, mid) + get(a, b, (id << 1) | 1, mid + 1, r);
    };

    function<void(ll, ll, ll, ll, ll, ll)> upd = [&](ll a, ll b, ll x, ll id, ll l, ll r){
        down(id, l, r); 

        if (b < l || a > r) return;
        if (a <= l && b >= r){
            val[id] += x * (r - l + 1);
            if (l != r){
                lazy[id << 1] += x;
                lazy[(id << 1) | 1] += x;
            }
            return;
        }
        
        ll mid = ((l + r) >> 1);
        upd(a, b, x, id << 1, l, mid);
        upd(a, b, x, (id << 1) | 1, mid + 1, r);
        val[id] = val[id << 1] + val[(id << 1) | 1];
    };
    
    // q次询问
    while (q--){
        cin >> opt >> a >> b;
        if (opt == 1){
            ll x; cin >> x;
            upd(a, b, x, 1, 1, N);
        }
        else{
            cout << get(a, b, 1, 1, N) << "\n";
        }
    }
    return 0;
}