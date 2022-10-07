double eps = 1e-9;
using Point = complex<double>;
struct Circle{ Point p; double r; };
double dist(Point p, Point q){ return abs(p-q); }
double area2(Point p, Point q){ return (conj(p)*q).imag();}
bool in(const Circle& c, Point p){ return dist(c.p, p) < c.r + eps; }
Circle INVAL = Circle{Point(0, 0), -1};
Circle mCC(Point a, Point b, Point c){
	b -= a; c -= a; 
	double d = 2*(conj(b)*c).imag(); if(abs(d)<eps) return INVAL;
	Point ans = (c*norm(b) - b*norm(c)) * Point(0, -1) / d;
	return Circle{a + ans, abs(ans)};
}
Circle solve(vector<Point> p) {
	mt19937 gen(0x94949); shuffle(p.begin(), p.end(), gen);
	Circle c = INVAL;
	for(int i=0; i<p.size(); ++i) if(c.r<0 ||!in(c, p[i])){
		c = Circle{p[i], 0};
		for(int j=0; j<=i; ++j) if(!in(c, p[j])){
			Circle ans{(p[i]+p[j])*0.5, dist(p[i], p[j])*0.5};
			if(c.r == 0) {c = ans; continue;}
			Circle l, r; l = r = INVAL;
			Point pq = p[j]-p[i];
			for(int k=0; k<=j; ++k) if(!in(ans, p[k])) {
				double a2 = area2(pq, p[k]-p[i]);
				Circle c = mCC(p[i], p[j], p[k]);
				if(c.r<0) continue;
				else if(a2 > 0 && (l.r<0||area2(pq, c.p-p[i]) > area2(pq, l.p-p[i]))) l = c;
				else if(a2 < 0 && (r.r<0||area2(pq, c.p-p[i]) < area2(pq, r.p-p[i]))) r = c;
			}
			if(l.r<0&&r.r<0) c = ans;
			else if(l.r<0) c = r;
			else if(r.r<0) c = l;
			else c = l.r<=r.r?l:r;
		}
	}
	return c;
}

