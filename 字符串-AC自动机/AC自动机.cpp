/*
AC�Զ��� + KMP + Trie��
����n��ģʽ����m���ı���
���m��, ÿ��֮�䶼��(n-1)���ո����, ��ʾģʽ���������ı����г��ֵĴ���
���ַ�����������Сд��ĸ�����֣� 
*/

/*
ʾ������:
3 2
A
AB
BA
ABCC
BABA

ʾ�����:
1 1 0
2 1 2
*/

#include <iostream>
#include <queue>
#include <cstring>
#include <vector>
using namespace std;
const int N = 100010; // �ڵ������� 

int tree[N][62];  // Trie��
vector<int> pats[N];  // �洢ÿ��β�ڵ��Ӧ��ģʽ������
int cnt[N];	 // �Ըýڵ�Ϊ��β��ģʽ������
int id = 0;

int fail[N];  // ʧ��ָ�빹�ɵ�����, ��ǰ�ַ����������ͬǰ��׺��Ӧ�Ľڵ� 

int turn(char c) {   // ��ϣ, �����ڴ����� 
    if (c >= '0' && c <= '9') return c - '0';  // [0,9]
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;  // [10,35]
    return c - 'A' + 36;  // [36,61]
}

void init_Trie() {		// ��ʼ��Trie�� 
	for (int i = 0; i <= id; ++i) {
		memset(tree[i], 0, sizeof(tree[i]));
		pats[i].clear();
		cnt[i] = 0;
	}	
	id = 0;
}

void func_add(const string& str, int i) {
	int p = 0;  // ��ǰָ�� 
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

void init_fail() {		// ��ʼ��Fail����
	memset(fail, 0, sizeof(fail));
	queue<int> q;
	
	for (int x = 0; x < 62; ++x) {
		if (tree[0][x]) q.push(tree[0][x]);	
	}

	while (!q.empty()) {
		int p = q.front(); q.pop();
        for (int x = 0; x < 62; x++) {
			int &tem = tree[p][x];  // ��������, �����޸�
            if (tem) {
                fail[tem] = tree[fail[p]][x];
                q.push(tem);
            }
			else {
                tem = tree[fail[p]][x];  // �ֽڵ㲻����ֱ��ѹ��·��
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
        
        // ���ݵ����ڵ㣨һ���ڵ�����к�׺ģʽ��������ͨ��ʧ�����ҵ���
        int temp = p;  // ����ֱ����p
        while (temp) {
            if (cnt[temp]) { 	// �����β�ڵ�
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
    
    // ����
    int n, m;
    cin >> n >> m;
	cin.ignore();	// ���Ի��з�, ǧ�������
    
    // ����Trie��
	init_Trie();
	for (int i = 1; i <= n; ++i) {
		string str;
		getline(cin, str);
		func_add(str, i);
	}
	 
	// ��ʼ��fail����, ������KMP�е�next
	init_fail();
	
    // ��m��ѯ�ʴ������ 
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
