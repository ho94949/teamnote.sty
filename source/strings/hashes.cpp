// deg[] = {1, P, P^2, P^3, ...}
// h[] = {0, s[0], s[0]*P + s[1], s[0]*P^2 + s[1]*P + s[2], ...}
const int MOD = (int)(1e9 + 7);
int h[MAXN], p[MAXN], P = max(239, (int)rnd());

void gen_hash(string s) {
	h[0] = 0, p[0] = 1;	
	int n = sz(s);
	for(int i = 0; i < n; i++) {
		h[i + 1] = (h[i] * 1LL * P + s[i]) % MOD;
		p[i + 1] = (p[i] * 1LL * P) % MOD;
	}
}

int get_hash(int l, int r) {
	return (h[r + 1] - (h[l] * 1LL * p[r - l + 1]) % MOD + MOD) % MOD;
}