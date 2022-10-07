vector<int> SA(const vector<int>& s, int upper) {
	int n=s.size();
	if (n == 0) return {};
	if (n == 1) return {0};
	if (n == 2) {
		if (s[0] < s[1]) return {0, 1};
		else return {1, 0};
	}
	vector<int> sa(n), sum_l(upper+1), sum_s(upper+1);
	vector<bool> ls(n);
	for (int i=n-2; i>=0; i--)
		ls[i]=(s[i] == s[i+1]) ? ls[i+1] : (s[i] < s[i+1]);
	for (int i = 0; i<n; i++)
		if (!ls[i]) sum_s[s[i]]++;
		else sum_l[s[i]+1]++;
	for (int i=0; i<=upper; i++) {
		sum_s[i] += sum_l[i];
		if (i < upper) sum_l[i+1] += sum_s[i];
	}
	auto induce=[&](const vector<int>& lms) {
		fill(sa.begin(), sa.end(), -1);
		vector<int> buf(upper+1);
		copy(sum_s.begin(), sum_s.end(), buf.begin());
		for (auto d : lms) {
			if (d == n) continue;
			sa[buf[s[d]]++] = d;
		}
		copy(sum_l.begin(), sum_l.end(), buf.begin());
		sa[buf[s[n-1]]++] = n-1;
		for (int i=0; i<n; i++) {
			int v=sa[i];
			if (v>=1 && !ls[v-1]) sa[buf[s[v-1]]++] = v-1;
		}
		copy(sum_l.begin(), sum_l.end(), buf.begin());
		for (int i=n-1; i>=0; i--) {
			int v=sa[i];
			if (v>=1 && ls[v-1]) sa[--buf[s[v-1]+1]] = v-1;
		}
	};
	vector<int> lms_map(n+1, -1), lms;
	int m=0;
	for (int i=1; i<n; i++) if (!ls[i-1] && ls[i]) {
		lms_map[i]=m++;
		lms.push_back(i);
	}
	induce(lms);
	if (m) {
		vector<int> sorted_lms, rec_s(m);
		for (int v : sa) if (lms_map[v] != -1) sorted_lms.push_back(v);
		int rec_upper=0;
		rec_s[lms_map[sorted_lms[0]]]=0;
		for (int i=1; i<m; i++) {
			int l=sorted_lms[i-1], r=sorted_lms[i];
			int end_l = (lms_map[l]+1 < m) ? lms[lms_map[l]+1] : n;
			int end_r = (lms_map[r]+1 < m) ? lms[lms_map[r]+1] : n;
			bool same=true;
			if (end_l-l != end_r-r) same=false;
			else {
				while (l < end_l) {
					if (s[l] != s[r]) break;
					l++, r++;
				}
				if (l == n || s[l] != s[r]) same=false;
			}
			if (!same) rec_upper++;
			rec_s[lms_map[sorted_lms[i]]]=rec_upper;
		}
		auto rec_sa = SA(rec_s, rec_upper);
		for (int i=0; i<m; i++) sorted_lms[i] = lms[rec_sa[i]];
		induce(sorted_lms);
	}
	return sa;
}

vector<int> lcp_array(const vector<int>& s, const vector<int>& sa) {
	int n=int(s.size());
	assert(n>=1);
	vector<int> rnk(n), lcp(n-1);
	for (int i=0; i<n; i++) rnk[sa[i]] = i;
	int h=0;
	for (int i=0; i<n; i++) {
		if (h > 0) h--;
		if (rnk[i] == 0) continue;
		int j=sa[rnk[i]-1];
		for (; j+h < n && i+h < n; h++)
			if (s[j+h] != s[i+h]) break;
		lcp[rnk[i]-1]=h;
	}
	return lcp;
}