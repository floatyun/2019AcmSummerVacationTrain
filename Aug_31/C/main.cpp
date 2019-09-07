#include <bits/stdc++.h>
using namespace std;

int main()
{
	int T;
	scanf("%d",&T);
	string A, sA, B, sB;
	int offset;
	int lA,lB;
	int t;
	for (int ti = 1; ti <= T; ++ti) {
		cin>>lA>>lB;
		cin>>A;
		cin>>sA;
		cin>>sB;
		offset = A[0]-sA[0];
		B.clear();
		for (auto x : sB) {
			t = x-'A';
			t += offset;
			t %= 26;
			t += 26;
			t %= 26;
			B.push_back(char(t+'A'));
		}
		printf("Case #%d: %s\n", ti, B.c_str());
	}
	return 0;
}