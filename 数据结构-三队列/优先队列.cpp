/*
优先队列 + 链表
一次操作: 找到最小元素并删去, 然后把其两侧的元素都加上删去的元素的大小, 元素一定非负
n代表数列大小, k代表操作次数
技巧: 变化一个元素相当于直接删去变化的元素并加上变化后的元素
*/

/*
示例输入:
5 3
1 4 2 8 7

示例输出:
17 7
*/


#include <bits/stdc++.h>
using ll = long long;
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    ll n, k;
    cin >> n >> k;
    ll round = n - k;   // 最后剩余的个数
    ll a[n + 1], l[n + 1], r[n + 1];  // l和r指的是a[i]所对应的数的左右索引，链表实现；+1是为了后面方便找head
    r[0] = 1;    // 找head
    for (ll i = 1; i <= n; i++){
        cin >> a[i];
        r[i] = i + 1;
        l[i] = i - 1;
    }
    
    priority_queue<pair<ll, ll>> q;  // <值，索引>，默认大根堆
    for (ll i = 1; i <= n; i++) q.push({-a[i], -i});  // 借负数实现小根堆

    while (k--){
        auto tem = q.top(); q.pop();  // 这个时候的最小值可能是还没来得及删除的元素
        while (-tem.first != a[-tem.second]){   // 值与当前实际a中的不同，就是应该删除的
            tem = q.top(); q.pop();   // 删除多余的元素
        }
        ll v = -tem.first, id = -tem.second;

        if (l[id] >= 1){     // 如果左边有元素才能操作，避免越界
            r[l[id]] = r[id];
            if (v != 0){
                a[l[id]] += v;
                q.push({-a[l[id]], -l[id]});  // v=0时不需要变化
            }
        }
        if (r[id] <= n){    // 如果右边有元素
            l[r[id]] = l[id];
            if (v != 0){
                a[r[id]] += v;
                q.push({-a[r[id]], -r[id]});
            }
        }
        if (l[id] == 0) r[0] = r[id];  // 单独提出来是为了找head
    }
    
    ll head = r[0];
    while (round--){
        cout << a[head] << " ";
        head = r[head];
    }
    return 0;
}