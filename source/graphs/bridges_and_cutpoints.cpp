void dfs(int v, int p = -1) {
	used[v] = 1;
	tin[v] = fup[v] = timer++;
	int ch = 0;
	for(auto to : gg[v]) {
		if(to == p) continue;
		if(used[to]) fup[v] = min(fup[v],tin[to]);
		else {
			dfs(to, v);
			fup[v] = min(fup[v], fup[to]);
			if(tin[v] < fup[to] && cnt[{min(to, v), max(to, v)}] < 2) 
				bridges.pb(id[{min(to, v), max(to, v)}]);
			if(p != -1 && tin[v] <= fup[to]) cutPoints.insert(v);
			ch++;
		}
	}
	if(p == -1 && ch > 1) cutPoints.insert(v);
}