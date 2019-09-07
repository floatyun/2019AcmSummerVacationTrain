#include <bits/stdc++.h>
using namespace std;

int main()
{
	freopen("in.txt","a",stdout);
	int n;
	cin>>n;
	int m = n * n;
	cout<<n<<" "<<m<<"\n";
	for (int i = 1; i <= n; ++i)
		for (int j = 1;j <= n; ++j)
			cout<<i<<" "<<j<<"\n";
	cout<<"\n\n";
	fclose(stdout);
}