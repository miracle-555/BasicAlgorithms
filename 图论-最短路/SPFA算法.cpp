/*
SPFA算法（优化后的Bellman-Ford）
n, m, k分别表示顶点数, 边数, 询问的源点
接着m行u, v, w, 表示有u到v的单向边, w为权值
（w可能为负数）
依次求出k到i的最短路(i从1到n且不为k), 不存在输出impossible（n-1行）
如果k在负权环内则只需要输出error
*/

/*
示例输入:
6 5 1
1 2 3
2 3 -2
3 4 1
1 5 4
3 5 2

示例输出:
3
1
2
3
impossible
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> graph(n + 1); 
	
	int u, v, w;
    while (m--) {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    
    // 核心部分
    vector<int> dist(n + 1, INT_MAX);
    dist[k] = 0;
    queue<int> q;
    vector<bool> is_inq(n + 1, false);  // 其实并非必须, 但可以提升效率
    q.push(k);
	is_inq[k] = true;
	
	vector<int> cnt(n + 1, 0); 
	
	while (!q.empty()) {
		int u = q.front(); q.pop();
		is_inq[u] = false;
		
		for (auto [v, w]: graph[u]) {
			if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
				dist[v] = dist[u] + w;
				cnt[v]++;
				if (cnt[v] >= n) {
					cout << "error";
                    return 0; 
				}
                if (!is_inq[v]) {
                    q.push(v);
                    is_inq[v] = true;
                }
			}
		}
	} 
	
	for (int i = 1; i <= n; ++i) {
		if (i != k) {
			if (dist[i] == INT_MAX) cout << "impossible\n";
			else cout << dist[i] << "\n";
		}
	}
	
    return 0;
}