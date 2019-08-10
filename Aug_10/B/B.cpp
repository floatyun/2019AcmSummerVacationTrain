#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	int n;
	cin>>n;
	map<int,int>val_to_last_index;
	int val;
	ll ans = 0;
	for (int i = 0;i < n; ++i) {
		cin>>val;
		auto it = val_to_last_index.find(val);
		int j;
		if (it == val_to_last_index.end())
			j = -1;
		else
			j = it->second;
		val_to_last_index[val] = i;
		ans += (ll)(i-j)*(ll)(n-i);
	}
	cout<<ans<<endl;
	return 0;
}