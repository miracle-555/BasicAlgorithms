/*
分块算法
数组N个元素, q次处理
opt为1表示[a, b]增加c
opt为2表示输出[a, b]的和
(输入端都是从1开始)
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

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll N, q, opt, a, b, c;
    cin >> N >> q;
    vector<ll> v(N);  // 目标数组
    for (ll& num: v) cin >> num;

    // 适配分块算法的几个变量
    ll width = sqrt(N + 1), Bnum = N % width? (N / width + 1): (N / width);  // 块的长度和个数
    ll gid[N], BL[Bnum], BR[Bnum], Bsum[Bnum] = {0};   // 数组中每个数组对应的分块下标, 每个分块的左索引、右索引以及和（不开数组, 直接用表达式也行）
    ll flag[Bnum] = {0};   // 表示该分块中每个元素需要被增加..., 减少复杂度
    for (ll i = 0; i < N; i++){
        gid[i] = i / width;
        Bsum[gid[i]] += v[i];
    }
    for (ll i = 0; i < Bnum; i++){
        BL[i] = i * width;
        BR[i] = min((i + 1) * width, N) - 1;
    }

    // q次询问
    while (q--){
        cin >> opt >> a >> b;
        a--; b--;    // 输入端都是从1开始 
        if (opt == 1){    // 增加
            cin >> c;
            if (gid[a] == gid[b]){
                for (ll i = a; i <= b; i++){
                    v[i] += c;
                }
                Bsum[gid[a]] += (b - a + 1) * c;
            }
            else{
                for (ll i = a; i <= BR[gid[a]]; i++){
                    v[i] += c;
                }
                for (ll i = b; i >= BL[gid[b]]; i--){
                    v[i] += c;
                }
                for (ll i = gid[a] + 1; i <= gid[b] - 1; i++){
                    flag[i] += c;
                }
                Bsum[gid[a]] += (BR[gid[a]] - a + 1) * c;
                Bsum[gid[b]] += (b - BL[gid[b]] + 1) * c;
            }
        }
        else{   // 取和
            ll ans = 0;
            if (gid[a] == gid[b]){
                for (ll i = a; i <= b; i++){
                    ans += v[i];
                }
                ans += flag[gid[a]] * (b - a + 1);   
            }
            else{
                for (ll i = gid[a] + 1; i <= gid[b] - 1; i++){
                    ans += Bsum[i] + flag[i] * (BR[i] - BL[i] + 1);
                }
                for (ll i = a; i <= BR[gid[a]]; i++){
                    ans += v[i];
                }
                for (ll i = b; i >= BL[gid[b]]; i--){
                    ans += v[i];
                }
                ans += (BR[gid[a]] - a + 1) * flag[gid[a]];
                ans += (b - BL[gid[b]] + 1) * flag[gid[b]];
            }
            cout << ans << "\n";
        }
    }

    return 0;
}