#include <bits/stdc++.h>
using namespace std;

int m;

struct mtr{
	int m;
	vector<vector<int>>__val;
	void get_double() {
		for (int i = 0; i < m; ++i) {
			auto &row = __val[i];
			for (int j = 0; j < m; ++j)
				row.push_back(row[j]);
		}
		for (int i = 0; i < m; ++i)
			__val.push_back(__val[i]);
		for (int i = m; i < 2*m; ++i) {
			auto &row = __val[i];
			for (int j = m; j < 2*m; ++j)
				row[j] = -row[j];
		}
		m <<= 1;
	}
	mtr() {
		m = 2;
		__val.resize(2);
		for (auto &row : __val) {
			row.resize(2);
			for (auto &cell : row)
				cell = 1;
		}
		__val[1][1] = -1;
	}
	void out() {
		for (auto &row : __val) {
			for (auto &cell : row)
				cout<<cell<<' ';
			cout<<"\n";
		}
	}
};

int main()
{
	mtr a;
	int m;
	cin >> m;
	while (a.m != m) a.get_double();
	a.out();
	return 0;
}