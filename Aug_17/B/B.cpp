#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<ll>len;
string S[]={"","COFFEE","CHICKEN"};
const int myn = 56;
const ll maxk = 1000000000000ll;

char solve(int n, ll k) {
	if (n <= 2) {
		return S[n][k];
	}
	if (k < len[n-2])
		return solve(n-2, k);
	else
		return solve(n-1, k-len[n-2]);
}

int main()
{
	len.push_back(0); // len(s[0])=0
	len.push_back(S[1].length()); // 1
	len.push_back(S[2].length()); // 2
	for (int i = 3;i <= myn+4; ++i) {
		len.push_back(len[i-1]+len[i-2]);
		//cout<<"i = "<<i<<"\t"<<len[i]<<"\t"<<(len[i]<(ll)(1e12))<<endl;
	}
	int t;
	cin>>t;
	int n;
	ll k;
	while (t--) {
		cin>>n>>k;
		--k;
		if (n >= myn) {
			if (n%2==1) n = myn+1; else n = myn;
		}
		string s="";
		for (int i = 0; i < 10; ++i) {
			if (k+i < len[n])
				s+=solve(n,k+i);
			else
				break;
		}
		cout<<s<<"\n";
	}
	return 0;
}
/*
CHICKENCOFFEECHICKENCOFFEECHICKENCHICKENCOFFEECHICKEN
 */