#include <vector>

using namespace std;

template<typename T>
class SegmentTree {
public:
	SegmentTree(int size) {
		N = size;
		tree.resize(size * 4); // roughly multiplied by 4
		lazy.resize(size * 4);
	}

	// update multiple elements
	void update(int start, int end, T val) {
		update(start, end, 1, N, 1, val);
	}

	// update single element
	void update(int index, T val) {
		update(index, index, val);
	}

	// get sum of range start to end
	T query(int start, int end) {
		return query(start, end, 1, N, 1);
	}

private:
	std::vector<T> tree; // segment tree, starting index is 1
	std::vector<T> lazy; // lazy propagation
	int N; // size of leaf node
	
	void lazyUpdate(int l, int r, int index) {
		tree[index] += lazy[index] * (r - l + 1);
		if (l != r) {
			lazy[index * 2] += lazy[index];
			lazy[index * 2 + 1] += lazy[index];
		}
		lazy[index] = 0;
	}

	T query(int start, int end, int l, int r, int index) {
		lazyUpdate(l, r, index);
		if (start > r || end < l) return 0;
		if (start <= l && r <= end) return tree[index];
		int mid = (l + r) / 2;
		return query(start, end, l, mid, index * 2) + query(start, end, mid + 1, r, index * 2 + 1);
	}

	void update(int start, int end, int l, int r, int index, T val) {
		lazyUpdate(l, r, index);
		if (start > r || end < l) return;
		else if (start <= l && r <= end) {
			lazy[index] += val;
			lazyUpdate(l, r, index);
		}
		else {
			int mid = (l + r) / 2;
			update(start, end, l, mid, index * 2, val);
			update(start, end, mid + 1, r, index * 2 + 1, val);
			tree[index] = tree[index * 2] + tree[index * 2 + 1];
		}
	}
};
