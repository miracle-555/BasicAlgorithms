/*
单调队列 + 二维滑动窗口
n和m代表矩阵v的行数和列数，a和b代表滑动窗口的大小
最后输出所有滑动窗口的最大值与最小值的乘积之和
对998244353取模
*/

/*
示例输入:
2 3 1 2
1 2 3
4 5 6

示例输出:
58
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;
const ll MOD = 998244353;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll n, m, a, b, res = 0;
    cin >> n >> m >> a >> b;
    ll v[n][m];
    for (ll i = 0; i < n; i++) for (ll j = 0; j < m; j++) cin >> v[i][j];

    ll v_subM[n][m - b + 1], v_subm[n][m - b + 1];  // 第一道压缩，分别储存列上连续b项的最值
    deque<ll> q;
    for (ll i = 0; i < n; i++){
        ll j = 0;
        for (; j < b - 1; j++){
            while (!q.empty() && v[i][j] >= v[i][q.back()]) q.pop_back();
            q.push_back(j);
        }
        for (; j < m; j++){
            while (!q.empty() && v[i][j] >= v[i][q.back()]) q.pop_back();
            q.push_back(j);
            if (q.front() <= j - b) q.pop_front();
            v_subM[i][j - b + 1] = v[i][q.front()];
        }
        q.clear();
        j = 0;
        for (; j < b - 1; j++){
            while (!q.empty() && v[i][j] <= v[i][q.back()]) q.pop_back();
            q.push_back(j);
        }
        for (; j < m; j++){
            while (!q.empty() && v[i][j] <= v[i][q.back()]) q.pop_back();
            q.push_back(j);
            if (q.front() <= j - b) q.pop_front();
            v_subm[i][j - b + 1] = v[i][q.front()];
        }
        q.clear();
    }

    deque<ll> q1, q2;    // 第二道压缩，分别代表最大值和最小值的
    for (ll j = 0; j < m - b + 1; j++){
        ll i = 0;
        for (; i < a - 1; i++){
            while (!q1.empty() && v_subM[i][j] >= v_subM[q1.back()][j]) q1.pop_back();
            q1.push_back(i);
            while (!q2.empty() && v_subm[i][j] <= v_subm[q2.back()][j]) q2.pop_back();
            q2.push_back(i);
        }
        for (; i < n; i++){
            while (!q1.empty() && v_subM[i][j] >= v_subM[q1.back()][j]) q1.pop_back();
            q1.push_back(i);
            if (q1.front() <= i - a) q1.pop_front();
            while (!q2.empty() && v_subm[i][j] <= v_subm[q2.back()][j]) q2.pop_back();
            q2.push_back(i);
            if (q2.front() <= i - a) q2.pop_front();
            res = (res + (v_subM[q1.front()][j] % MOD) * (v_subm[q2.front()][j] % MOD)) % MOD;
        }
        q1.clear();
        q2.clear();
    }
    
    cout << res;
    return 0;
}