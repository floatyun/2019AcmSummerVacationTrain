#include <bits/stdc++.h>
using namespace std;

void cut_seg(string &s, size_t &pos, string &res, char c) {
  // s[pos]不确定
  // zero
  if (pos == string::npos || pos >= s.length()) {
    res = "";
    pos = string::npos;
    return;
  }
  if (s[pos] != c) {
    res = "";
    return;
  }
  auto r = s.find_first_not_of(c, pos);
  if (r == string::npos)
    res = s.substr(pos);
  else
    res = s.substr(pos, r - pos);
  pos = r;
}

bool is_perfect(string& s) {
  // return a+b<=b+a;
  int l = s.length();
  string ss = s + s;
  for (int i = 1; i < l; ++i)
    if (ss.substr(i, l) < s) return false;
  return true;
}

void work() {
  string s, seg;
  cin >> s;
  int l = s.length();
	int i = 0;
	while (i < l) {
		for (int j = l-i; j > 0; --j) {
			seg = s.substr(i,j);
			if (is_perfect(seg)) {
				cout<<seg<<" ";
				i += j;
				break;
			}
		}
	}
	cout<<"\n";
}

int main() {
  int t;
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> t;
  while (t--) work();
  return 0;
}