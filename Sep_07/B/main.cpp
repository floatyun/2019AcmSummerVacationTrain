#include <bits/stdc++.h>
using namespace std;
//#define debugmode
map<int,int>f;
int Q(int a) {
	if (!f.count(a)) return a;
	if (a == f[a]) {
		return a;
	} else {
		int t = Q(f[a]);
		f[a] = t;
		return t;
	}
}

int n,q;
int main()
{
	scanf("%d%d",&n,&q);
	int o,a;
	for (int i = 0; i < q; ++i) {
		scanf("%d%d",&o,&a);
		if (o == 1) { // mark
			if (!f.count(a)) {
				f[a] = a+1;
				int t = Q(a);
				#ifdef debugmode
				  printf("t1 = %d\n", t);
				#else
				#endif
			}
			if (a < 1 || a > n) continue;
		} else { // query
			int t = Q(a);
			#ifdef debugmode
				printf("t2 = %d\n", t);
			#else
			#endif
			if (t > n) t = -1;
			printf("%d\n",t);
		}
	}
}