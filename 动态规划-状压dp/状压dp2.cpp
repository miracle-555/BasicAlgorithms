/*
状压dp + 滚动数组优化
n是行数, m是列数, 接下来是n行m列的01矩阵
1处不能种农作物, 0处可以, 且农作物之间不能相邻
输出最多能种植多少农作物
*/

/*
示例输入:
2 3
1 0 0
1 1 1

示例输出:
1
*/

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll n, m, tem;
    cin >> n >> m;
    ll ST = (1 << m);
    vector<ll> b(n, 0);  // 指block
    for (ll i = 0; i < n; i++){
        for (ll j = 0; j < m; j++){
            cin >> tem;
            b[i] |= (tem << j);
        }
    }

    // 可以提前准备好的数据
    vector<ll> prob;   // 可能存在的情况
    for (ll k = 0; k < ST; k++){
        if ((k & (k << 1)) == 0 && (k & (k >> 1)) == 0)   // 与左右都无相邻; 位运算记得括号
            prob.push_back(k);
    }
    ll H = prob.size();
    map<ll, ll> cnt;    // cnt[s]表示s中含1的个数
    for (auto tem: prob){
        ll s = tem;
        while (s){
            cnt[tem] += (s & 1);
            s >>= 1;
        }
    }

    function<int(ll, ll)> chk = [&](ll s1, ll s2){   // 情况是否合法
        return (s1 & s2) == 0;
    };

    vector<ll> dp_pre(ST, 0), dp_now(ST, 0);   // 类似于滚动数组
    for (ll i = 0; i < n; i++){
        dp_pre = dp_now;
        for (auto now: prob){
            if (chk(b[i], now) == 0) continue;   // 剪去不合法情况
            ll tem = cnt[now];
            for (auto pre: prob){
                if (chk(now, pre)){   // 剪去不合法情况
                    dp_now[now] = max(dp_now[now], dp_pre[pre] + tem);
                }
            }    
        }
    }

    cout << *max_element(dp_now.begin(), dp_now.end());
    return 0;
}