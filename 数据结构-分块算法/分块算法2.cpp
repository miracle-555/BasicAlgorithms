/*
分块算法
数组N个元素, q次处理
opt为1表示[a, b]增加c
opt为2表示输出[a, b]中比c小的个数
(输入端都是从1开始)
*/

/*
示例输入:
5
1 2 3 4 5
4
2 1 3 2
2 2 4 4
1 3 3 2
2 1 5 5

示例输出:
1
2
3
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using ll = long long;
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    ll N, q;
    cin >> N;
    vector<ll> v(N);
    for (ll& num: v) cin >> num;
    cin >> q;

    // 预处理
    ll width = sqrt(N + 1), Bnum = N % width? (N / width + 1): (N / width);
    ll gid[N], BL[Bnum], BR[Bnum];
    ll flag[N] = {0};    // 块级别的增量标记
    vector<vector<ll>> vsort(Bnum);
    for (ll i = 0; i < N; i++){
        gid[i] = i / width;
    }
    for (ll i = 0; i < Bnum; i++){
        BL[i] = i * width;
        BR[i] = min((i + 1) * width, N) - 1;
        for (ll j = BL[i]; j <= BR[i]; j++){
            vsort[i].push_back(v[j]);
        }
        sort(vsort[i].begin(), vsort[i].end());
    }

    // 函数定义
    auto add_and_sort = [&](ll l, ll r, ll id, ll num){  // 第id块[l, r]添加num后并重新排序
        for (ll i = l; i <= r; i++){    // 更新原始数组
            v[BL[id] + i] += num;
        }
        vsort[id].clear();       // 清空排序数组, 重新排序
        for (ll j = BL[id]; j <= BR[id]; j++) {
            vsort[id].push_back(v[j]);
        }
        sort(vsort[id].begin(), vsort[id].end());
    };

    auto func_cal = [&](ll id, ll num){   // 二分查找
        ll l = 0, r = vsort[id].size(), mid;
        while (l < r){
            mid = (l + r) / 2;
            if (vsort[id][mid] < num) l = mid + 1;
            else r = mid;
        }
        return l;
    };

    // 询问
    while (q--){
        ll opt, a, b, c;
        cin >> opt >> a >> b >> c;
        a--; b--;    // 减1适配
        ll ia = gid[a], ib = gid[b];
        if (opt == 1){    // 增加
            if (ia == ib){
                add_and_sort(a - BL[ia], b - BL[ib], gid[a], c);
            }
            else{
                for (ll i = ia + 1; i <= ib - 1; i++){
                    flag[i] += c;
                }
                add_and_sort(a - BL[ia], BR[ia] - BL[ia], ia, c);
                add_and_sort(0, b - BL[ib], ib, c);
            }
        }
        else{   // 找比其小的个数
            ll ans = 0;
            if (ia == ib){
                c -= flag[ia];
                for (ll i = a; i <= b; i++){
                    if (v[i] < c) ans++;
                }
            }
            else{
                for (ll i = ia + 1; i <= ib - 1; i++){
                    ans += func_cal(i, c - flag[i]);
                }
                for (ll i = a; i <= BR[ia]; i++){
                    if (v[i] < c - flag[ia]) ans++;
                }
                for (ll i = b; i >= BL[ib]; i--){
                    if (v[i] < c - flag[ib]) ans++;
                }
            }
            cout << ans << "\n";
        }
    }

    return 0;
}