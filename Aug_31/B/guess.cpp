#include <bits/stdc++.h>
using namespace std;

bool is_sorted(vector<int>&a, int n) {
	for (int i = 0; i < n-1; ++i)
		if (a[i] > a[i-1]) return false;
	return true;
}

int main()
{
	int n;
	int k;
	scanf("%d%d",&n,&k);
	vector<int>b(n),a(n);
	for (int i = 0; i < n; ++i) b[i] = i;
	int sorted_cnt = 0;
	do {
		string s(80,'#');
		cout<<s<<endl;
		for (int i = 0; i < n; ++i) a[i] = b[i];
		for (int i = 0; i < n; ++i) cout<<a[i]<<" ";
		cout<<endl;
		for (int i = 0; i < k; ++i) {
			for (int j = 1; j < n; ++j)
				if (a[j-1] > a[j]) {
					swap(a[j-1], a[j]);
				} else {
					//++sorted_cnt;
				}
		}
		if (is_sorted(a,n)) ++sorted_cnt;
		for (int i = 0; i < n; ++i) cout<<a[i]<<" ";
		cout<<endl;
	} while (next_permutation(b.begin(), b.end()));
	cout<<sorted_cnt<<endl;
}