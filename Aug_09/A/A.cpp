#include <bits/stdc++.h>
using namespace std;

const int kNo = 1;
const int kYes = 2;
const int kNoInput = 0;

struct myset {
  int sz;
  int n;
  vector<int> p;
  myset(int sz) : sz(sz), p(sz) {
    n = sz / 2;
    for (int i = 0; i < sz; ++i) p[i] = i;
  }
  int get_p(int a) { return a == p[a] ? a : p[a] = get_p(p[a]); }
  inline int anti(int a) { return a < n ? a + n : a - n; }
	int merge(int a, int b) {
		//cout<<"merge "<<a<<" "<<b<<" "<<endl;
		a = get_p(a);
		b = get_p(b);
		//cout<<"merge2 "<<a<<" "<<b<<" "<<endl;
		p[a] = b;
	}
};

vector<int> A(10000), B(10000), Good(1000), Bad(1000);

int work() {
  int n, m, x, y;
  cin >> n >> m >> x >> y;
  if (cin.fail()) return kNoInput;
  myset my(2 * (n + 1));
  int a, b, anti_a, anti_b;
  for (int i = 0; i < m; ++i) cin >> A[i] >> B[i];
  for (int i = 0; i < x; ++i) cin >> Good[i];
  for (int i = 0; i < y; ++i) cin >> Bad[i];
  for (int i = 0; i < m; ++i) {
    a = A[i] - 1;
    b = B[i] - 1;
    anti_a = my.anti(a);
    anti_b = my.anti(b);
		a = my.get_p(a);
    b = my.get_p(b);
    anti_a = my.get_p(anti_a);
    anti_b = my.get_p(anti_b);
    if (a == b || anti_a == anti_b) return kNo;
		my.merge(a,anti_b);
		my.merge(anti_a,b);
  }
	for (int i = 0; i < x; ++i) {
		a = Good[i]-1;
		b = my.anti(n);
		anti_a = my.anti(a);
    anti_b = my.anti(b);
		a = my.get_p(a);
    b = my.get_p(b);
    anti_a = my.get_p(anti_a);
    anti_b = my.get_p(anti_b);
    if (a == b || anti_a == anti_b) return kNo;
		my.merge(a,anti_b);
		my.merge(anti_a,b);
	}
	for (int i = 0; i < y; ++i) {
		a = Bad[i]-1;
		b = n;
		anti_a = my.anti(a);
    anti_b = my.anti(b);
		a = my.get_p(a);
    b = my.get_p(b);
    anti_a = my.get_p(anti_a);
    anti_b = my.get_p(anti_b);
    if (a == b || anti_a == anti_b) return kNo;
		my.merge(a,anti_b);
		my.merge(anti_a,b);
	}
	int cnt = 0;
	for (int i = 0;i <= n; ++i)
		cnt += (i == my.get_p(i));
	if (cnt > 2) return kNo;
  return kYes;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int res;
  while (true) {
    res = work();
    if (kNoInput == res) break;
    if (kNo == res)
      cout << "NO\n";
    else
      cout << "YES\n";
  }
  return 0;
}