/*
线性dp
N表示店的总数, M表示花的总数
初始有2斗酒
遇到店：酒量加倍
遇到花：喝掉1斗酒
最后一次遇到的是花, 且正好喝光
问一共有多少种店和花的排列方案数, 结果对MOD取模
*/

/*
示例输入:
5 10

示例输出:
14
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const ll MOD = 1000000007;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    
    ll N, M;
    cin >> N >> M;

    ll dp[N + 1][M + 1][M + 1];   // 酒一定不会超过花数
    memset(dp, 0, sizeof(dp));

    dp[0][0][2] = 1;   // 是刚刚好的方案数

    for (ll i = 0; i <= N; i++)     // 要都从0开始
        for (ll j = 0; j <= M - 1; j++)
            for (ll k = 1; k <= M; k++){   // dp[i][j][0]不需要讨论
                if (i >= 1 && (k & 1) == 0){    // 位运算优先度一般很低, 记得时常括
                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j][k / 2]) % MOD;
                }
                if (j >= 1 && k + 1 <= M){
                    dp[i][j][k] = (dp[i][j][k] + dp[i][j - 1][k + 1]) % MOD;
                }   
            }

    cout << dp[N][M - 1][1];
    return 0;
}