#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

template<typename T>
class Dijkstra {
public:
	vector<T> dijk; // result
	vector<bool> visit; // false if not reachable

	// vertex index is starting with 1
	Dijkstra(int v) {
		V = v;
		graph.resize(V + 1);
		visit.resize(V + 1);
		dijk.resize(V + 1);

		// Roughly large value to prevent overflow
		T maxValue = numeric_limits<T>::max() / 2;

		for (int i = 1; i <= V; i++) {
			dijk[i] = maxValue;
		}
	}

	// unidirectional(one-way)
	void addEdge(int s, int e, T cost) {
		graph[s].push_back(make_pair(cost, e));
	}

	void findShortestPath(int source) {
		dijk[source] = 0;
		pq.push(make_pair(0, source));

		while (!pq.empty()) {
			T val = pq.top().first;
			int index = pq.top().second;
			pq.pop();
			if (visit[index]) continue;
			visit[index] = true;
			dijk[index] = val;
			for (auto i : graph[index]) {
				if (visit[i.second]) continue;
				pq.push(make_pair(val - i.first, i.second));
			}
		}

		for (int i = 1; i <= V; i++) {
			dijk[i] *= -1;
		}
	}

private:
	vector<vector<pair<T, int>>> graph;
	priority_queue<pair<T, int>> pq;
	int V;
};
