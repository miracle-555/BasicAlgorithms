/*
01背包 + 完全背包
N和V表示物品件数和背包最大容量(承重)
w和v分别表示物品的体积(重量)和价值
分别输出两个数字, 分别代表物品只有一件时和有无穷件时
*/

/*
示例输入:
5 20
1 6
2 5
3 8
5 15
3 3

示例输出:
37
120
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll N, V, w, v;
    cin >> N >> V;
    vector<ll> dp1(V + 1, 0);   // dp1中的是能够，所以最后取末值
    vector<ll> dp2(V + 1, 0);   // dp2中的是刚刚好，所以最后遍历取最大值

    for (ll i = 0; i < N; i++){
        cin >> w >> v;
        for (ll j = V; j >= 0; j--) if (j >= w) dp1[j] = max(dp1[j], dp1[j - w] + v);
        for (ll j = 0; j <= V; j++) if (j >= w) dp2[j] = max(dp2[j], dp2[j - w] + v);
    }
    
    cout << dp1[V] << "\n" << *max_element(dp2.begin(), dp2.end());
    return 0;
}