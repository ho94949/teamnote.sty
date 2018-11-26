int lca(int u, int v) {
	if(depth[u] > depth[v]) swap(u, v);
	for(int i = LOG2MAXN - 1; i >= 0; i--) 
		if(depth[v] - depth[u] >= (1 << i))
			v = dp[i][v];
	if(u == v) return u;
	for(int i = LOG2MAXN - 1; i >= 0; i--)
		if(dp[i][v] != dp[i][u]) {
			u = dp[i][u];
			v = dp[i][v];
		}
	return dp[0][u];
}