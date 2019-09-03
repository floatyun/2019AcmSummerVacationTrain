#include <bits/stdc++.h>
using namespace std;
int n;
int main() {
	int n;
	cin>>n;
	uint32_t t;
	int ans = 0;
	while (n--) {
		cin>>t;
		for (int i = 0;i < 4; ++i) {
			ans += ((t&0xff)=='a');
			t >>= 8;
		}
	}
	cout<<ans<<endl;
	return 0;
}