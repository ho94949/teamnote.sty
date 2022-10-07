template <int MAXC = 26> struct AhoCorasick {
	vector<array<int, MAXC>> C;
	vector<int> F;
	vector<vector<int>> FG;
	vector<bool> E;

	int node() {
		int r = C.size();
		E.push_back(0);
		F.push_back(-1);
		C.emplace_back();
		fill(C.back().begin(), C.back().end(), -1);
		return r;
	}
	int ctrans(int n, int c) {
		if (C[n][c] == -1) C[n][c] = node();
		return C[n][c];
	}
	int ftrans(int n, int c) const {
		while (n && C[n][c] == -1) n = F[n];
		return C[n][c] != -1 ? C[n][c] : 0;
	}
	AhoCorasick(vector<vector<int>> P) {
		node();
		for (int i = 0; i < (int)P.size(); i++) {
			int n = 0;
			for (int c : P[i]) n = ctrans(n, c);
			E[n] = 1;
		}
		queue<int> Q;
		F[0] = 0;
		for (int c : C[0]) if (c != -1) Q.push(c), F[c] = 0;
		while (!Q.empty()) {
			int n = Q.front(); Q.pop();
			for (int c = 0; c < MAXC; ++c) if (C[n][c] != -1) {
				int f = F[n];
				while (f && C[f][c] == -1) f = F[f];
				F[C[n][c]] = C[f][c] != -1 ? C[f][c] : 0;
				Q.emplace(C[n][c]);
			}
		}
		FG.resize(F.size());
		for (int i = 1; i < (int)F.size(); i++) {
			FG[F[i]].push_back(i);
			if (E[i]) Q.push(i);
		}
		while (!Q.empty()) {
			int n = Q.front();
			Q.pop();
			for (int f : FG[n]) E[f] = 1, Q.push(f);
		}
	}
	bool check(vector<int> V) {
		if (E[0]) return 1;
		int n = 0;
		for (int c : V) {
			n = ftrans(n, c);
			if (E[n]) return 1;
		}
		return 0;
	}
};
