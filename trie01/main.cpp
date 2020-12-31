#include <bits/stdc++.h>
using namespace std;

struct TrieNode01 {
	int child[2], val;
}tr[32 * 100005];

int cnt;

void build(int x) {
	int rt = 0;
	for (int i = 31; i >= 0; --i) {
		int c = (x >> i) & 1;
		if (tr[rt].child[c] == -1)tr[rt].child[c] = ++cnt;
		rt = tr[rt].child[c];
	}
	tr[rt].val = x;
}

int query(int x) {
	int rt = 0;
	for (int i = 31; i >= 0; --i) {
		int c = (x >> i) & 1;
		if (tr[rt].child[c ^ 1] != -1)rt = tr[rt].child[c ^ 1];
		else
			rt = tr[rt].child[c];
		if (rt == -1)return -1;
	}
	return tr[rt].val;
}

int main() {
	cnt = 0;
	//initialize into -1 in case query range contains 0;
	memset(tr, -1, sizeof tr);
	vector<int>nums{ 0,1,3,5,6,8,14,22 };
	for (int x : nums) {
		build(x);
		cout << (query(x) ^ x) << endl;
	}
}