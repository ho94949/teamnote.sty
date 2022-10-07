template <class S, S (*op)(S, S), S (*e)(),
	class F, S (*mapping)(F, S), F (*composition)(F, F), F (*id)()>
class LazySeg {
	int N, log;
	vector<S> d;
	vector<F> lz;

	void pull(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
	void put(int k, F f) {
		d[k] = mapping(f, d[k]);
		if (k < N) lz[k] = composition(f, lz[k]);
	}
	void push(int k) {
		put(2 * k, lz[k]);
		put(2 * k + 1, lz[k]);
		lz[k] = id();
	}
public:
	LazySeg() : LazySeg(0) {}
	explicit LazySeg(int n) : LazySeg(vector<S>(n, e())) {}
	explicit LazySeg(const vector<S> &v) {
		log = 31 - __builtin_clz(v.size() | 1);
		N = 1 << log;
		d = vector<S>(2 * N, e());
		lz = vector<F>(N, id());
		for (int i = 0; i < (int)v.size(); i++) d[N + i] = v[i];
		for (int i = N - 1; i >= 1; i--) pull(i);
	}
	void set(int p, S x) {
		p += N;
		for (int i = log; i >= 1; i--) push(p >> i);
		d[p] = x;
		for (int i = 1; i <= log; i++) pull(p >> i);
	}
	S prod(int l, int r) {
		if (l == r) return e();
		l += N, r += N;
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r - 1) >> i);
		}
		S sml = e(), smr = e();
		while (l < r) {
			if (l & 1) sml = op(sml, d[l++]);
			if (r & 1) smr = op(d[--r], smr);
			l >>= 1, r >>= 1;
		}
		return op(sml, smr);
	}
	S all_prod() { return d[1]; }
	void apply(int l, int r, F f) {
		if (l == r) return;
		l += N, r += N;
		for (int i = log; i >= 1; i--) {
			if (((l >> i) << i) != l) push(l >> i);
			if (((r >> i) << i) != r) push((r - 1) >> i);
		}
		int l2 = l, r2 = r;
		while (l < r) {
			if (l & 1) put(l++, f);
			if (r & 1) put(--r, f);
			l >>= 1, r >>= 1;
		}
		l = l2, r = r2;
		for (int i = 1; i <= log; i++) {
			if (((l >> i) << i) != l) pull(l >> i);
			if (((r >> i) << i) != r) pull((r - 1) >> i);
		}
	}
};