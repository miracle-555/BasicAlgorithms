/*
Floyd�㷨
n��m�ֱ��ʾ�ڵ���������
������m�е�u, v, w����ʾ��u��v��һ��Ȩ��Ϊw�������
����������, ���ܵ��ͰѸ�λ����Ϊinf
������ڸ�Ȩ��, �����Negative cycle found
��������0-based�ģ�
*/

/*
ʾ������:
4 5
0 1 5
0 3 10
1 2 3
2 3 1
3 1 -2

ʾ�����:
0 5 8 9 
inf 0 3 4 
inf -1 0 1 
inf -2 1 0
*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	// �㷨���Ĳ���
	vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
	for (int i = 0; i < n; ++i) dist[i][i] = 0;
	
    int u, v, w;
	while (m--) {
		cin >> u >> v >> w;
		dist[u][v] = w;
	}

	for (int k = 0; k < n; ++k) {
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX) {
					dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
				}
			}
		}
	}
	
	for (int i = 0; i < n; ++i) {
		if (dist[i][i] < 0) {
			cout << "Negative cycle found";
			return 0;
		}
	}
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (dist[i][j] != INT_MAX) cout << dist[i][j] << " ";
            else cout << "inf ";  
		}
		cout << "\n";
	}
	
	return 0;
} 