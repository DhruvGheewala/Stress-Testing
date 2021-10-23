#include <bits/stdc++.h>
#include "generator.hpp"
using namespace std;

#define endl '\n'
#define int int64_t

mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int l, int r) {
	if(l > r) swap(l, r);
	return std::uniform_int_distribution<int>(l, r)(rng);
}

vector<int> generateVector(int n, int l, int r) {
	const int offset = (l < 0 ? -l : 0);
	l += offset;
	r += offset;

	vector<int> res(n);
	for(int i = 0; i < n; i++)
		res[i] = rnd(l, r) - offset;
	return res;
}

vector<int> generateUniqueVector(int n, int l, int r) {
	assert(n <= r - l + 1);

	const int offset = (l < 0 ? -l : 0);
	l += offset;
	r += offset;

	set<int> s;
	while(s.size() < n)
		s.insert(rnd(l, r) - offset);

	vector<int> res(s.begin(), s.end());
	shuffle(res.begin(), res.end(), rng);
	return res;
}

string generateString(int n, const string &chars) {
	assert(chars.size() > 0);
	int l = 0, r = chars.size() - 1;

	string res(n, '#');
	for(int i = 0; i < n; i++)
		res[i] = chars[rnd(l, r)];
	return res;
}

vector<pair<int, int>> generateUndirectedGraph(int n) {
	int maximum_edges = n * (n - 1) / 2;
	int edges = rnd(1, maximum_edges);

	vector<bool> take(maximum_edges, false);
	for(int i = 0; i < edges; i++) take[i] = true;
	shuffle(take.begin(), take.end(), rng);

	int index = 0;
	vector<pair<int, int>> res;
	res.reserve(edges);
	for(int i = 1; i <= n; i++) {
		for(int j = i + 1; j <= n; j++) {
			if(take[index]) {
				if(rnd(0, 1)) res.push_back({i, j});
				else res.push_back({j, i});

				if(edges == 1) return res;
				edges--;
			}
			index++;
		}
	}
	return res;
}

vector<pair<int, int>> generateDirectedGraph(int n) {
	int minimum_edges = n - 1;
	int maximum_edges = n * (n - 1);
	int edges = rnd(minimum_edges, maximum_edges);

	vector<bool> take(maximum_edges, false);
	for(int i = 0; i < edges; i++) take[i] = true;
	shuffle(take.begin(), take.end(), rng);

	int index = 0;
	vector<pair<int, int>> res;
	res.reserve(edges);
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			if(i == j) continue;

			if(take[index]) {
				res.push_back({i, j});
				if(edges == 1) return res;
				edges--;
			}
		}
	}
	return res;
}

void shuffleEdges(vector<pair<int, int>> &edges, bool undir) {
	int n = 0;
	for(const auto &[u, v]: edges)
		n = max({n, u, v});

	vector<int> p(n + 1);
	iota(p.begin(), p.end(), 0);
	shuffle(p.begin() + 1, p.end(), rng);
	shuffle(edges.begin(), edges.end(), rng);

	for(auto &[u, v]: edges) {
		if(undir && rnd(0, 1)) swap(u, v);
		u = p[u];
		v = p[v];
	}
}

vector<pair<int, int>> generateRopeGraph(int n, bool undir) {
	vector<pair<int, int>> edges(n - 1);
	for(int i = 1; i < n; i++)
		edges[i - 1] = {i, i + 1};
	shuffleEdges(edges, undir);
	return edges;
}

vector<pair<int, int>> generateStarGraph(int n, bool undir) {
	vector<pair<int, int>> edges(n - 1);
	for(int i = 2; i <= n; i++)
		edges[i - 2] = {1, i};
	shuffleEdges(edges, undir);
	return edges;
}

vector<pair<int, int>> generateTree(int n) {
	int option = rnd(0, 2);

	if(option == 0)
		return generateRopeGraph(n, true);
	else if(option == 1)
		return generateStarGraph(n, true);

	vector<pair<int, int>> res;
	res.reserve(n);
	for(int i = 2; i <= n; i++)
		res.push_back({rnd(1, i - 1), i});
	shuffleEdges(res, true);
	return res;
}

vector<pair<int, int>> generateConnectedGraph(int n) {
	vector<pair<int, int>> res = generateTree(n);
	for(int rep = 0; rep < 10; rep++) {
		int x = rnd(1, n);
		int y = rnd(1, n);
		if(x > y) swap(x, y);
		if(x != y) res.push_back({x, y});
	}
	sort(res.begin(), res.end());
	res.erase(unique(res.begin(), res.end()), res.end());
	shuffleEdges(res, true);
	return res;
}

#undef endl
#undef int
