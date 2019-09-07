#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, q;
const int kMaxN = 200005;
const int kMaxQ = 100005;
const double eps = 1e-6;

ll h[kMaxN], H[kMaxN];
struct qnd {
  int i;
  int l;
  int r;
  double f_val;
  double ans;
  bool solved;
};
bool cmp_bylr(const qnd& a, const qnd& b) { return a.l > b.l || (a.l == b.l && a.r < b.r); }
bool cmp_byi(const qnd& a, const qnd& b) { return a.i < b.i; }
vector<qnd> in_query;
ll sum_h, max_h;

namespace modui{
	int H[];
};

void solve(qnd& q) {
	if (q.solved) return;
	double u_l = 0, u_r = max_h, u_m; // 始终保证 ans \in [u_l,u_r)
	while (u_r-u_l >= eps) {
		u_m = (u_l+u_r)/2;

		ll cnt = query_cnt(q.l, q.r, u_m);
		ll sum = query_sum(q.l, q.r, u_m);

		double f_val = cnt*u_m - sum; // cal f(u)
		if (f_val > q.f_val) { // cut too much
			u_r = u_m;
		} else if (abs(f_val-q.f_val) < eps) {
			q.ans = max_h - u_m;
			q.solved = true;
			break;
		} else {
			u_l = u_m;
		}
	}
	q.ans = max_h - u_m;
	q.solved = true;
}

int main() {
  ios::sync_with_stdio(0);
  cin >> n >> q;
  for (int i = 0; i < n; ++i) cin >> h[i];
  max_h = *max_element(h, h + n);
  for (int i = 0; i < n; ++i) {
    sum_h += h[i];
    H[i] = max_h - h[i];
  }
  in_query.clear();
  int l, r, x, y;
  for (int i = 0; i < q; ++i) {
    cin >> l >> r >> x >> y;
		--l; --r;
    if (x < y)
      in_query.emplace_back(
          qnd{i, l, r, (double)x / (double)y * (double)sum_h, 0, false});
    else
      in_query.emplace_back(
          qnd{i, l, r, (double)x / (double)y * (double)sum_h, 0, true});
  }
  sort(in_query.begin(), in_query.end(), cmp_byl);
  // solve
  for (auto& x : in_query) {
    solve(x);
  }

  // out the ans
  sort(in_query.begin(), in_query.end(), cmp_byi);
  for (auto& x : in_query) cout << x.ans << "\n";
  return 0;
}