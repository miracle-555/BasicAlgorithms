/*
分组背包dp 
第一行两个整数N和V, 分别代表组的个数与背包最大容量 
接下来N组数据
每组第一行一个整数S, 表示该组物品数量
接下来S行每行两个整数v和w, 表示该组中S个物品的体积和价值
*/

/*
示例输入:
3 5
2
1 2
2 4
3
1 2
2 3
3 4
2
2 1
3 5

示例输出:
9
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	// 输入 	
	int N, V;
	cin >> N >> V;

	vector<vector<pair<int, int>>> a(N);
	for (int i = 0; i < N; ++i) {
		int S, v, w;
		cin >> S;
		a[i].resize(S);
		for (int j = 0; j < S; ++j) {
			cin >> v >> w;
			a[i][j] = {v, w};
		}
	}
	
	// dp求解过程 
	vector<int> dp(V + 1, 0);
	dp[0] = 0;
	for (int i = 0; i < N; ++i)	{
		for (int j = V; j >= 0; --j) {
			for (auto [v, w]: a[i]) {
				if (j >= v) dp[j] = max(dp[j], dp[j - v] + w);
			}
		}
	}
	
	cout << dp[V];
	return 0;
}