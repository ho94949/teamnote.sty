// returns the number of solutions
int gauss() {
	// n - number of equations
	// m - number of variables
	int m = n;
	memset(where, -1, sizeof(where));
	for(int row = 0, col = 0; col < m && row < n; col++) {
		int sel = row;
		//[PARTIAL PIVOTING]
		for(int i = row; i < n; i++) 
			if(abs(aa[i][col]) > abs(aa[sel][col]))
				sel = i;
		// if no pivot - skip this line
		// means that variable #col is independent
		if(abs(aa[sel][col]) < EPS) continue;
		// else swap two lines
		for(int i = col; i <= m; i++) swap(aa[sel][i], aa[row][i]);
		where[col] = row;
		//[/PARTIAL PIVOTING]
		//[KILL EVERYBODY IN THIS COL]
		for(int i = 0; i < n; i++) 
			if(i != row) {
				double c = aa[i][col] / aa[row][col];
				for(int j= col; j <= m; j++) 
					aa[i][j] -= aa[row][j] * c;
			}
		//[/KILL EVERYBODY IN THIS COL]
		row++;
	}
	// count ans
	for(int i = 0; i < m; i++) 
		if(where[i] != -1)
			ans[i] = aa[where[i]][n] / aa[where[i]][i];
	// check if any solution exist
	for(int i = 0; i < n; i++) {
		double sum = 0;
		for(int j = 0; j < m; j++) 
			sum += ans[j] * aa[i][j];
		if(abs(sum - aa[i][m]) > EPS) return 0;
	}
	// check if we have independent variables
	for(int i = 0; i < m; i++) if(where[i] == -1) return INF;
	return 1;
}