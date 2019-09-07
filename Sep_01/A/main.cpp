#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define debugmode

struct node;
struct node{
		int x,y;
		ll w;
	};
int n,m;
const int kMaxM = 1e+5;
vector<node>V;

ll cal(int x,int y) { // 计算x,y所填的数
	ll ans;
	int story = min(x, n + 1 - x);
	story = min(story, y);
	story = min(story, n + 1 - y);
	ans = 4*(n-story+1)*(story-1);
	if (x == story) {
		return ans + 2*(n-2*story+1) + (y-story) + 1;
	} else if (y == story) {
		return ans + (n-2*story+1) + ((n + 1 - story) - x) + 1;
	} else if (y == n+1-story && x != n+1-story) {
		return ans + 3*(n-2*story+1) + (x - story) + 1;
	} else {
		return ans + 0 + ((n+1-story) - y) + 1;
	}
}
ll f(ll a) { // a >= 0
	ll ans = 0;
	while (a) {ans += a%10; a/=10;}
	return ans;
}
ll get_palace_val(int x, int y) { // x,y必须是一个宫殿点
	return f(cal(x,y));
}
void init() {
	scanf("%d%d",&n,&m);
	V.resize(m);
	int x, y;
	for (int i = 0; i < m; ++i) {
		scanf("%d%d",&x,&y);
		V[i].x = x;
		V[i].y = y;
		V[i].w = get_palace_val(x,y);
		#ifdef debugmode
			printf("(%d,%d) %lld %lld\n", x, y , cal(x,y), V[i].w);
		#else
		#endif
	}
}

int main()
{
	init();
}