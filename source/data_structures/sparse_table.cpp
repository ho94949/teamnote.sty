int st[LOG2MAXN][MAXN], lg[MAXN];
int n;

void initST() {
	for(int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
	for(int i = 1; i < LOG2MAXN; i++) 
		for(int j = 0; j < n - (1 << (i - 1)); j++) 
			st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
}

int queryST(int l, int r) {
	int curlg = lg[r - l + 1];
	return min(st[curlg][l], st[curlg][r - (1 << (curlg)) + 1]);
}