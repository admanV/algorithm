// https://www.acmicpc.net/problem/10999

#include <iostream>
#include <cstdio>
#include <vector>

#define ll long long

using namespace std;

vector<ll>tree;
vector<ll>lazy;
vector<ll>d;

ll init(int idx, int l, int r) {
	if (l == r) return tree[idx] = d[l];
	else return tree[idx] = init(idx * 2, l, (l + r) / 2) + init(idx * 2 + 1, (l + r) / 2 + 1, r);
}

void update(int idx, int start, int end, int l, int r, ll val) {
	if (lazy[idx] != 0) {
		if (start != end) {
			lazy[idx * 2] += lazy[idx];
			lazy[idx * 2 + 1] += lazy[idx];
		}
		tree[idx] += (end - start + 1) * lazy[idx];
		lazy[idx] = 0;
	}

	if (l > end || r < start) return;

	if (l <= start && end <= r) {
		if (start != end) {
			lazy[idx * 2] += val;
			lazy[idx * 2 + 1] += val;
		}
		tree[idx] += (end - start + 1) * val;
		return;
	}

	int mid = (start + end) / 2;
	update(idx * 2, start, mid , l, r, val);
	update(idx * 2 + 1, mid + 1, end, l, r, val);
	tree[idx] = tree[idx * 2] + tree[idx * 2 + 1];
}

ll getSUM(int idx, int start, int end, int l, int r) {
	if (lazy[idx] != 0) {
		if(start != end) {
			lazy[idx * 2] += lazy[idx];
			lazy[idx * 2 + 1] += lazy[idx];
		}
		tree[idx] += (end - start + 1) * lazy[idx];
		lazy[idx] = 0;
	}

	if (l > end || r < start) return 0;
	if (l <= start && end <= r) return tree[idx];

	int mid = (start + end) / 2;
	return getSUM(idx * 2, start, mid, l, r) + getSUM(idx * 2 + 1, mid + 1, end, l, r);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, k; cin >> n >> m >> k;
	d.resize(n + 1);
	for (int i = 1; i <= n; i++) cin >> d[i];

	int st;

	for (st = 1; st < n; st *= 2);
	st *= 2;

	tree.resize(st);
	lazy.resize(st);
	init(1, 1, n);

	for (int i = 0; i < m + k; i++) {
		int q, l, r; cin >> q >> l >> r;
		if (q == 1) {
			ll v; cin >> v;
			update(1, 1, n, l, r, v);
		}
		else cout << getSUM(1, 1, n, l, r) << "\n";
	}
}