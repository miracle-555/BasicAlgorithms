/*
���鱳��dp 
��һ����������N��V, �ֱ������ĸ����뱳��������� 
������N������
ÿ���һ��һ������S, ��ʾ������Ʒ����
������S��ÿ����������v��w, ��ʾ������S����Ʒ������ͼ�ֵ
*/

/*
ʾ������:
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

ʾ�����:
9
*/

#include <iostream>
#include <vector>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	// ���� 	
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
	
	// dp������ 
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