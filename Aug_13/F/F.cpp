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
		if (n&1)
			cout<<flag+n/2<<"/"<<(flag^1)+n/2<<"\n";
		else
			cout<<"1/1\n";
	}
	return 0;
}