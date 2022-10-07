template <typename T>
vector<T> char_poly(vector<vector<T>> M) {
	int N = M.size();
    for (int i = 0; i < N - 2; i++) {
		int p = -1;
		for (int j = i + 1; j < N; j++)
			if (M[j][i] != T(0)) {
				p = j; break;
			}
		if (p == -1) continue;
		M[i + 1].swap(M[p]);
		for (int j = 0; j < N; j++) swap(M[j][i + 1], M[j][p]);

		T r = T(1) / M[i + 1][i];
		for (int j = i + 2; j < N; j++) {
			T c = M[j][i] * r;
			for (int k = 0; k < N; k++) M[j][k] -= M[i + 1][k] * c;
			for (int k = 0; k < N; k++) M[k][i + 1] += M[k][j] * c;
		}
	}
	vector<vector<T>> P = {{T(1)}};
	for (int i = 0; i < N; i++) {
		vector<T> f(i + 2, 0);
		for (int j = 0; j <= i; j++) f[j + 1] += P[i][j];
		for (int j = 0; j <= i; j++) f[j] -= P[i][j] * M[i][i];

		T b = 1;
		for (int j = i - 1; j >= 0; j--) {
			b *= M[j + 1][j];
			T h = -M[j][i] * b;
			for (int k = 0; k <= j; k++) f[k] += h * P[j][k];
		}
		P.push_back(f);
	}
	return P.back();
}

template <typename T>
vector<T> det_linear(vector<vector<T>> A, vector<vector<T>> B) {
	int N = A.size(), nu = 0; T det = 1;
	for (int i = 0; i < N; i++) {
		int p = -1;
		for (int j = i; j < N; j++)
			if (A[j][i] != T(0)) {
				p = j; break;
			}
		if (p == -1) {
			if (++nu > N) return vector<T>(N + 1, 0);
			for (int j = 0; j < i; j++) {
				for (int k = 0; k < N; k++)
				    B[k][i] -= B[k][j] * A[j][i];
				A[j][i] = 0;
			}
			for (int j = 0; j < N; j++) swap(A[j][i], B[j][i]);
			--i; continue;
		}
		if (p != i) A[i].swap(A[p]), B[i].swap(B[p]), det = -det;
		det *= A[i][i];

		T c = T(1) / A[i][i];
		for (int j = 0; j < N; j++) A[i][j] *= c, B[i][j] *= c;
		for (int j = 0; j < N; j++) if (j != i) {
			T c = A[j][i];
			for (int k = 0; k < N; k++)
			    A[j][k] -= A[i][k] * c, B[j][k] -= B[i][k] * c;
		}
	}
	for (auto &y : B) for (T &x : y) x = -x;
	auto f = char_poly(B);
	for (T &x : f) x *= det;
	f.erase(f.begin(), f.begin() + nu);
	f.resize(N + 1);
	return f;
}
