#include <bits/stdc++.h>
using namespace std;
const int N = 100;
vector<bool>f(N+5);
int g[N+5][N+5];

bool cal_g(int n, int x) {
	// [1..x]
	if (n <= x) return true;
	if (-1 != g[n][x]) return g[n][x];
	for (int y = 1; y <= x; ++y) {
		if (false == cal_g(n-y, 2*y)) {
			return g[n][x] = true;
		}
	}
	return g[n][x] = false;
}

bool cal_f(int n) {
	for (int x = 1; x < n; ++x) {
		if (false == cal_g(n-x,2*x))
			return true;
	}
	return false;
}

int main()
{
	f[0] = false;
	f[1] = true;
	f[2] = 0;
	memset(g,-1,sizeof(g));
	for (int i = 3; i <= N; ++i)
		f[i] = cal_f(i);
	for (int i = 0; i <= N; ++i) {
		printf("f(%d) = %d\n",i,(int)f[i]);
	}
	printf("_____");
	for (int i = 0; i <= N; ++i) if (!f[i]) printf("%d ",i);
	puts("end");
}