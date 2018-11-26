inverse[1] = 1;
for (int i = 2; i < p; i++)
	inverse[i] = (p - (p / i) * inverse[p % i] % p) % p;