/*
{
    x = a[i] % p[i]
    ..
}
=> x == a[i] % p[i]
=> x == y[1] + y[2] * p[2] + y[3] * p[1] * p[2] + ...
r[i][j] = p[i] ^ (-1) mod p[j]
a[1] = x[1]
a[2] = x[1] + x[2] * p[1]
x[2] = (a[2] - x[1]) * r[1][2]
...
*/
for (int i=0; i<k; ++i) {
	x[i] = a[i];
	for (int j=0; j<i; ++j) {
		x[i] = r[j][i] * (x[i] - x[j]);
 
		x[i] = x[i] % p[i];
		if (x[i] < 0)  x[i] += p[i];
	}
}