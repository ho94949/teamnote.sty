int safe(int x) {
	return x >= n ? x - n : x;
}

void build() {
	for (int i = 0; i < n; ++i) {
		c[i] = s[i] - 31;
		begin[c[i] + 1]++;
		suf[i] = i;
	}
	for (int i = 0; i + 1 < A; ++i)
		begin[i + 1] += begin[i];
	for (int l = 0; l < n; l = (l ? l * 2 : 1)) {
		for (int i = 0; i < n; ++i) {
			pos = safe(suf[i] - l + n);
			new_suf[begin[c[pos]]++] = pos;
		}
		for (int i = 0, total = 0; i < n; ++i) {
			if ((i == 0) || (c[new_suf[i - 1]] != c[new_suf[i]]) || (c[safe(new_suf[i - 1] + l)] != c[safe(new_suf[i] + l)]))
				begin[total++] = i;
			new_c[new_suf[i]] = total - 1;
		}
		memcpy(suf, new_suf, n * sizeof(suf[0]));
		memcpy(c, new_c, n * sizeof(c[0]));
	}
}