#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n,m;
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	while (true) {
		cin>>n>>m;
		int flag = n>m ? 1 : 0;
		if (n == 0 && m == 0) break;
		auto d = __gcd(n,m);
		n /= d; m /= d;
		n += m-1;
		int b = flag+n/2;
		int w = flag+n/2;
		int k = d/2;
		int r = d&1;
		int B = k*n+r*b;
		int W = k*b+r*w;
		int dd = __gcd(B,W);
		B /= dd;
		W /= dd;
		cout<<B<<"/"<<W<<"\n";
	}
	return 0;
}