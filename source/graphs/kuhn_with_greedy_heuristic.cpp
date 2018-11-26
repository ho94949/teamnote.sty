bool try_kuhn(int v) {
	used[v] = 1;
	for(auto to : gg[v]) 
		if(mt[to] == -1 || (mt[to] != -1 && !used[mt[to]] && try_kuhn(mt[to]))) {
			mt[to] = v;
			rmt[v] = to;
			return 1;
		}
	return 0;
}

void solve() {
	memset(mt, -1, sizeof(mt));
	memset(rmt, -1, sizeof(rmt));
	while(1) {
		bool any = 0;
		memset(used, 0, sizeof(used));
		for(int i = 0; i < n; i++) 
			if(rmt[i] == -1)
				any |= try_kuhn(i);
		if(!any) break;
	}
	vpii ans;
	for(int i = 0; i < n; i++) if(rmt[i] != -1) ans.pb({i + 1, rmt[i] + 1});
	cout << sz(ans) << endl;
	for(auto x : ans) cout << x.fi << ' ' << x.se << endl; 
}