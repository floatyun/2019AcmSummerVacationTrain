#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool work(string &s, int &l, int &cnt) {
	vector<char>p(l+2);
	p[0] = p[1] = '#';
	int n = 2;
	int c = 0;
	for (int i = 0; i < l; ++i) {
		if (s[i] == p[n-1] && s[i] == p[n-2]) {
			n -= 2;
			++c;
		} else {
			p[n++] = s[i];
		}
	}
	cnt += c;
	return false;
}

int main()
{
	string s;
	cin>>s;
	int cnt = 0;
	int l = s.length();
	while (work(s, l, cnt)) ;
	cout<<cnt<<endl;
	return 0;
}