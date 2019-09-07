#include <bits/stdc++.h>
using namespace std;
const double pi = 4*atan(1);
typedef struct point vec;
struct point{
	double x, y;
	void init() {
		scanf("%lf%lf",&x,&y);
	}
	vec operator -(const vec&b) const {
		return point{x-b.x, y-b.y};
	}
	vec operator +(const vec&b) const {
		return vec{x+b.x, y+b.y};
	}
	double length() const {
		return sqrt(x*x+y*y);
	}
	double operator *(const vec &b) const { // dot
		return x*b.x+y*b.y;
	}
};

double get_angle(const vec&a, const vec&b) {
	return acos(a*b/a.length()/b.length());
}

double solve() {
	int n;
	scanf("%d",&n);
	vector<point> p(n);
	point q;
	for (auto &x : p) x.init();
	q.init();
	double ans = 0;
	vector<vec> vecs(n);
	for (int i = 0; i < n; ++i) vecs[i] = p[(i+1)%n]-p[i];
	for (int i = 0; i < n; ++i) {
		auto j = (i+1)%n; // p[j] rotate around p[j]
		// vecs[i] and vecs[j]
		auto r = (q-p[j]).length();
		ans += r * get_angle(vecs[i], vecs[j]);
	}
	return ans;
}

int main()
{
	int t;
	scanf("%d",&t);
	for (int ti = 1; ti <= t; ++ti) {
		auto ans = solve();
		printf("Case #%d: %.03lf\n", ti, ans);
	}
	return 0;
}