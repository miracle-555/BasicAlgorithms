/*
Dijkstra算法
n个城市, m条双向路
接下来m行u, v, w, 指u与v之间有一条距离为w的路
（w一定大于0） 
依次求出城市1到城市i的最短路(i=2,3,...,n)
不存在输出-1 
*/

/*
示例输入:
4 5
1 2 2
1 3 4
2 3 1
2 4 6
3 4 3

示例输出:
2
3
6 
*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	vector<vector<int>> graph(n + 1, vector<int>(n + 1, INT_MAX));
	
	int u, v, w;
	while (m--) {
		cin >> u >> v >> w;
		graph[u][v] = w;
		graph[v][u] = w;
	}

	vector<int> dist(n + 1, INT_MAX);
	dist[1] = 0;
	vector<bool> is_visited(n + 1, false);
	
	priority_queue<pair<int, int>> qp;
	qp.push({0, 1});

	while (!qp.empty()) {
		int u = qp.top().second; qp.pop();
		if (is_visited[u]) continue;
		is_visited[u] = true;
		
		for (int v = 1; v <= n; ++v) {
			if (graph[u][v] != INT_MAX) {
				if (dist[u] + graph[u][v] < dist[v]) {
					dist[v] = dist[u] + graph[u][v];
					qp.push({-graph[u][v], v});
				}
			}
		}
	}
	
	for (int i = 2; i <= n; ++i) {
		if (dist[i] != INT_MAX) cout << dist[i] << "\n";
		else cout << "-1\n";
	}
	return 0;
}