/*
AC自动机 + KMP + Trie树
给定n个模式串与m个文本串
输出m行, 每行之间都用(n-1)个空格隔开, 表示模式串依次在文本串中出现的次数
（字符仅仅包括大小写字母与数字） 
*/

/*
示例输入:
3 2
A
AB
BA
ABCC
BABA

示例输出:
1 1 0
2 1 2
*/

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
const int N = 100010; // 节点数上限 

int tree[N][62];  // Trie树
vector<int> pats[N];  // 存储每个尾节点对应的模式串索引
int cnt[N];	 // 以该节点为结尾的模式串数量
int id = 0;

int fail[N];  // 失配指针构成的数组, 当前字符串的最长真相同前后缀对应的节点 

int turn(char c) {   // 哈希, 减少内存消耗 
    if (c >= '0' && c <= '9') return c - '0';  // [0,9]
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;  // [10,35]
    return c - 'A' + 36;  // [36,61]
}

void init_Trie() {		// 初始化Trie树 
	for (int i = 0; i <= id; ++i) {
		memset(tree[i], 0, sizeof(tree[i]));
		pats[i].clear();
		cnt[i] = 0;
	}	
	id = 0;
}

void func_add(const string& str, int i) {
	int p = 0;  // 当前指针 
	for (char ch: str) {
		int x = turn(ch);
		if (!tree[p][x]) {
			tree[p][x] = ++id;
		}
		p = tree[p][x];
	}
	pats[p].push_back(i);
	cnt[p]++;	
}

void init_fail() {		// 初始化Fail数组
	memset(fail, 0, sizeof(fail));
	queue<int> q;
	
	for (int x = 0; x < 62; ++x) {
		if (tree[0][x]) q.push(tree[0][x]);	
	}

	while (!q.empty()) {
		int p = q.front(); q.pop();
        for (int x = 0; x < 62; x++) {
			int &tem = tree[p][x];  // 设置引用, 便于修改
            if (tem) {
                fail[tem] = tree[fail[p]][x];
                q.push(tem);
            }
			else {
                tem = tree[fail[p]][x];  // 字节点不存在直接压缩路径
            }
        }		
	}
}

vector<int> func_find(const string& str, int n) {
	vector<int> ans(n + 1, 0);
	int p = 0;
	
    for (char ch: str) {
        int x = turn(ch);
        p = tree[p][x];
        
        // 回溯到根节点（一个节点的所有后缀模式串都可以通过失配链找到）
        int temp = p;  // 不能直接用p
        while (temp) {
            if (cnt[temp]) { 	// 如果是尾节点
                for (int id: pats[temp]) {
                    ans[id]++;
                }
            }
            temp = fail[temp];
        }
    }
    return ans;
}
    
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    
    // 输入
    int n, m;
    cin >> n >> m;
	cin.ignore();	// 忽略换行符, 千万别忘了
    
    // 构建Trie树
	init_Trie();
	for (int i = 1; i <= n; ++i) {
		string str;
		getline(cin, str);
		func_add(str, i);
	}
	 
	// 初始化fail数组, 类似于KMP中的next
	init_fail();
	
    // 对m次询问处理输出 
    while (m--) {
    	string str;
    	getline(cin, str);

		vector<int> ans = func_find(str, n);
		for (int i = 1; i <= n; ++i) {
            cout << ans[i];
            if (i < n) cout << " ";
        }
        cout << "\n";
	}
	
	return 0;
} 
