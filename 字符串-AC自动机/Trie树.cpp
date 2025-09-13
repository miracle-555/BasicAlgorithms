/*
Trie树
T表示数据总数
每一组下n和q分别表示模式串个数和查询串个数
每次查询, 输出存在多少个模式串, 使得查询串是此模式串的前缀
（字符串中只存在大小写字母和数字, 保证节点数上限不超过3*10**6）
*/

/*
示例输入:
3
3 3
fusufusu
fusu
anguei
fusu
anguei
kkksc
5 2
fusu
Fusu
AFakeFusu
afakefusu
fusuisnotfake
Fusu
fusu
1 1
998244353
9

示例输出:
2
1
0
1
2
1
*/

#include <iostream>
#include <cstring>
using namespace std;
const int N = 3000010; // 节点数上限

int tree[N][62];  // tree[i][j]指的是节点编号为i的元素为j的子节点的编号, 根节点为0
int cnt[N];   // cnt[i]指包含编号为i的节点的模式串的个数, 一般根据题目具体而定
int id = 0;   // 为树上每个节点编号, 唯一

int turn(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;  
    return c - 'A' + 36;
}


void func_add(const string& s) {
    int p = 0, c;  // p指处理到字符串的哪一位（用编号唯一表示）
    for (char ch: s) {
        c = turn(ch);
        if (!tree[p][c]) tree[p][c] = ++id;
        p = tree[p][c];
        cnt[p]++;
    }
}

int func_query(const string& s) {
    int p = 0, c;
    for (char ch: s) {
        c = turn(ch);
        if (!tree[p][c]) return 0;
        p = tree[p][c];
    }
    return cnt[p];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int T;
    cin >> T;
    
    while (T--) {
        int n, q;
        string str;
        cin >> n >> q;

        // 只初始化使用过的部分
        for (int i = 0; i <= id; ++i) {
            memset(tree[i], 0, sizeof(tree[i]));
            cnt[i] = 0;
        }
        id = 0;

        while (n--) {
            cin >> str;
            func_add(str);            
        }
        while (q--) {
            cin >> str;
            cout << func_query(str) << "\n";
        }   
    }
    
    return 0;
}