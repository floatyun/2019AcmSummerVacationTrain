#include <bits/stdc++.h>
using namespace std;
typedef uint64_t ll;
int main()
{
	ll n,m;
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	while (true) {
		cin>>n>>m;
		if (n == 0 && m == 0) break;
		ll d = __gcd(n,m);
		n /= d; m /= d;
		if (n == m) {
			cout<<"1/0\n";
			continue;
		}
		if (n%2 != m%2) {
			cout<<"1/1\n";
			continue;
		}
		if (n > m) swap(n,m);
		ll t = (n+1)/2*(n+1);
		ll u = m-n-1;
		u /= 2;
		t += u*n;
		cout<<t<<"/"<<t-1<<"\n";	
	}
	return 0;
}