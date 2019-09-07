#include <bits/stdc++.h>
using namespace std;

struct jiwan_isomers{
	string name;
	vector<int>deg;
	jiwan_isomers(){}
	jiwan_isomers(string s, int a[]) {
		name = s;
		deg.clear();
		for (int i = 0;i < 6; ++i) deg.push_back(a[i]);
	}
	void set_deg(int a[]) {
		deg.clear();
		for (int i = 0;i < 6; ++i) deg.push_back(a[i]);
	}
	bool is_same(jiwan_isomers &b) {
		for (int i = 0; i < 6; ++i)
			if (deg[i] != b.deg[i])
				return false;
		return true;
	}
};

vector<jiwan_isomers>known;
string names[] = {
	"n-hexane",
	"3-methylpentane",
	"2,2-dimethylbutane",
	"2-methylpentane",
	"2,3-dimethylbutane"
};
int a[][6] = {
1,1,2,2,2,2,
1,1,1,2,2,3,
1,1,1,1,2,4,
1,1,1,2,2,33, // 手动修正为33
1,1,1,1,3,3,
};

void work() {
	int d[6];
	int dd[6];
	vector<int>to[6];
	memset(d,0,sizeof(d));
	int a,b;
	for (int i = 0; i < 5; ++i) {
		cin>>a>>b;
		--a; --b;
		++d[a]; ++d[b];
		to[a].push_back(b);
		to[b].push_back(a);
	}
	memcpy(dd,d,sizeof(d));
	sort(d,d+6);
	if (d[5] == 3 && d[4] != 3) {
		// 1,1,1,2,2,3,
		// i point to the vertex whose deg is 3
		int i;
		for (i = 0; i < 6; ++i) if (dd[i] == 3) break;
		int one = 0, two = 0;
		for (auto from : to[i])
			if (dd[from] == 1)
				++one;
			else
				++two;
		if (one == 2 && two == 1) {
			d[5] = 33; // 手动修正为33
		}
	}
	jiwan_isomers tmp;
	tmp.set_deg(d);
	for (auto &x : known)
		if (x.is_same(tmp)) {
			cout<<x.name<<"\n";
			return;
		}
}

int main()
{
	for (int i = 0; i < 5; ++i)
		known.push_back(jiwan_isomers(names[i], a[i]));
	int t;
	cin>>t;
	while (t--) work();
}