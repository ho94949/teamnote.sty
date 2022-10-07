int find_centroid(const vector<vector<int>> &G, const vector<bool> &used, int v) {
	vector<tuple<int, int, int>> sz;
	function<void(int, int)> dfs = [&](int a, int p) {
		int S = 1, mx = 0;
		for (int x : G[a]) if (x != p && !used[x]) {
            dfs(x, a);
            int c = get<1>(sz.back());
            S += c, mx = max(mx, c);
        }
		sz.emplace_back(a, S, mx);
	};
	dfs(v, -1);
	int S = get<1>(sz.back());
	for (auto [i, s, mx] : sz) if (2 * max(S - s, mx) <= S) return i;
}
answer_type solve(const vector<vector<int>>& G) {
	vector<bool> used(size(G), 0);
	answer_type answer;
	auto work = [&](int c) {
        /* Do something on rooted tree c
           DFS with !used[x] (See above) */
	};
	queue<int> Q; Q.emplace(0);
	while (!Q.empty()){
		int x = Q.front();
		Q.pop();
		int c = find_centroid(G, used, x);
		work(c);
		used[c] = 1;
		for (int x : G[c]) if (!used[x]) Q.emplace(x);
	}
	return answer;
}