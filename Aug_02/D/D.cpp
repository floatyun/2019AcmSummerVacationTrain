#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 1005;
const int kMaxM = 1005;
const int kMaxV = 1000;
typedef long long ll;
int n,k;
int ans;
vector<int>items;
vector<int>boxes;

bool put(int v) {
	for (auto &b : boxes)
		if (v <= b) {
			b -= v;
			return true;
		}
	return false;
}

bool can_contain(int m) {
	boxes.clear();
	boxes.resize(k, m);
	for (auto v : items)
		if (!put(v))
			return false;
	return true;
}

void work(int cid) {
  cin >> n >> k;
	items.resize(n);
	int mx = 0, sum = 0;
	for (auto &i : items) {
		cin>>i;
		mx = max(mx,i);
		sum += i;
	}
	sort(items.begin(), items.end(), greater<int>());
	int l = 0, r = n*kMaxV;
	// (l,r]
	// while (l+1 < r) {
	// 	int m = (l+r)/2;
	// 	if (can_contain(m))
	// 		r = m;
	// 	else
	// 		l = m;
	// }
	for (int r = max(mx, sum/k); r <= n*kMaxV; ++r)
		if (can_contain(r)) {
			ans = r;
			break;
		}
	cout<<"Case #"<<cid<<": "<<ans<<endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i)
		work(i);
  return 0;
}