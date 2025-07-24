/*
单调队列+一维滑动窗口
n代表数组a的大小，k代表滑动窗口的大小
第一排连续输出滑动窗口的最小值
第二排连续输出滑动窗口的最大值
*/

/*
示例输入:
8 3
1 3 1 3 5 3 6 7

示例输出:
1 1 1 3 3 3 
3 3 5 5 6 7 
*/

#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll n, k;
    cin >> n >> k;
    ll a[n];
    for (ll i = 0; i < n; i++) cin >> a[i];

    deque<ll> p;   // 实现单调递增的队列，储存对应数字的索引(用索引才能知道什么时候该丢掉)
    ll i = 0;
    for (; i < k - 1; i++){
        while (!p.empty() && a[i] <= a[p.back()]) p.pop_back();
        p.push_back(i);
    }
    for (; i < n; i++){
        while (!p.empty() && a[i] <= a[p.back()]) p.pop_back();
        p.push_back(i);
        if (p.front() <= i - k) p.pop_front();
        cout << a[p.front()] << " ";
    }
    cout << "\n";

    p.clear();   // 实现单调递减的队列，储存对应数字的索引
    i = 0;
    for (; i < k - 1; i++){
        while (!p.empty() && a[i] >= a[p.back()]) p.pop_back();
        p.push_back(i);
    }
    for (; i < n; i++){
        while (!p.empty() && a[i] >= a[p.back()]) p.pop_back();
        p.push_back(i);
        if (p.front() <= i - k) p.pop_front();
        cout << a[p.front()] << " ";
    }

    return 0;
}
