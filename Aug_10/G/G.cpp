#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool work(string &s, int &l, int &cnt) {
	string p;
	int i = 0;
	int c = 0;
	while (i < l) {
		if (i+1 >= l || s[i+1] != s[i]) {
			p += s[i];
			++i;
			continue;
		}
		if (i+2 >= l || s[i+2] != s[i]) {
			p += s[i];
			p += s[i+1];
			i += 2;
		} else {
			// 消除
			++c;
			i += 3;
		}
	}
	s = p;
	l -= 3*c;
	cnt += c;
	return c;
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