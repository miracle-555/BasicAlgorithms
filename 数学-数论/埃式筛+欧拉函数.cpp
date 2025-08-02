/*
埃氏筛 + 欧拉函数
T表示询问次数, num是T个要求的数字
求的是num的最小素因子和欧拉函数值
欧拉函数:不超过num且与num互素的自然数个数
*/

/*
示例输入:
5
2
10
17
100
12345

示例输出:
2 1
2 4
17 16
2 40
3 6576
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

const ll N = 10000000;
int is_prime[N + 1];   // 为了避免主函数上栈空间溢出（N特别大）, 定义在全局空间中
ll ans[N + 1];
ll phi[N + 1];

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    // 对全局空间中三个数组的初始化
    is_prime[0] = is_prime[1] = 0;
    for (ll i = 2; i <= N; i++) is_prime[i] = 1;

    ans[0] = ans[1] = -1;
    for (ll i = 2; i <= N; i++) ans[i] = LLONG_MAX;    // 初始化为无穷大, 便于后面min处理

    for (ll i = 0; i <= N; i++) phi[i] = i;

    // 埃筛, 同时中间处理ans与phi
    for (ll i = 2; i <= N; i++){
        if (is_prime[i]){
            ans[i] = i;
            phi[i] = i - 1;         // 注意如此求Euler函数的根本原理
            for (ll j = i * 2; j <= N; j += i){   // 一般埃式筛从i**2开始会更加接近O(N), 不过本代码是为了适配其他所需
                is_prime[j] = 0;
                ans[j] = min(ans[j], i);
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }

    // 输入与输出
    ll T;
    cin >> T;
    while (T--){
        ll num;
        cin >> num;
        cout << ans[num] << " " << phi[num] << "\n";
    }

    return 0;
}