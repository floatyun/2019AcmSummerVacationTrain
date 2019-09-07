#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1000000000;
vector<ll>f;

ll power(ll a, int n) {
	ll ans = 1;
	while (n--) ans *= a;
	return ans;
}

int main()
{
	f.push_back(0);
	f.push_back(1);
	for (int i = 2; i <= 10; ++i)
		f.push_back(f[i-1]+f[i-2]);
	ll sum = 0;
	for (auto x : f) {
		sum += x;
		cout<<sum<<", ";
	}
	cout<<endl;
	for (int m = 2; m <= 5; ++m) {
		sum = 0;
		for (auto x : f) {
			sum += power(x,m);
			cout<<sum<<", ";
		}
		cout<<endl;
	}
	return 0;
}