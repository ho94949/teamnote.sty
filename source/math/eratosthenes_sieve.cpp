int lp[N+1];
vi pr;
for (int i = 2; i <= N; i++) {
	if (lp[i] == 0) {
		lp[i] = i;
		pr.push_back (i);
	}
	for (int j = 0; j < sz(pr) && pr[j] <= lp[i] && i * pr[j] <= N; j++)
		lp[i * pr[j]] = pr[j];
}