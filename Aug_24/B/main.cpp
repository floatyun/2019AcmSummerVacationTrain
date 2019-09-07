#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int N = 10002;
const ll kMaxDis = 10000000000000ll;
int n,m;
struct nd{
	int to;
	ll w;
};
ll ans;
vector<nd>from[N];
bool vis[N];
ll dis[N];
int max_mid[N];
struct qnd{
	int v;
	int max_mid; // 这个max_mid是包含了v这个点的比较，因为队列里面拿出来是要去拓展的。
	ll dis;
	bool operator <(const qnd& b) const {
		// b is top
		return (dis > b.dis) || (dis == b.dis && max_mid > b.max_mid);
	}
};

void clear() {
	for (int i = 1; i <= n; ++i) from[i].resize(0);
	ans = 0;
}

void dij_clear() {
	memset(vis, false, sizeof(vis));
	for (int i = 1; i <= n; ++i) dis[i] = kMaxDis;
	memset(max_mid,0,sizeof(max_mid));
}

void init() {
	scanf("%d%d",&n,&m);
	int u,v,w;
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d",&u,&v,&w);
		from[u].emplace_back(nd{v,w});
		from[v].emplace_back(nd{u,w});
	}
}

void dij(int s) {
	dij_clear();
	priority_queue<qnd> q;
	dis[s] = 0;
	max_mid[s] = 0;
	q.emplace(qnd{s,0,0});
	while (!q.empty()) {
		auto u = q.top();
		q.pop();
		if (vis[u.v]) continue;
		vis[u.v] = true;
		for (auto &e : from[u.v]) {
			if (dis[e.to] > e.w + dis[u.v]) {
				dis[e.to] = e.w + dis[u.v];
				max_mid[e.to] = u.max_mid;
				q.emplace(qnd{e.to, max(e.to, u.max_mid), dis[e.to]});
			} else if (dis[e.to] == e.w + dis[u.v] && u.max_mid < max_mid[e.to]) {
				max_mid[e.to] = u.max_mid;
				q.emplace(qnd{e.to,max(e.to, u.max_mid), dis[e.to]});
			}
		}
	}
}

void count(int s) {
	for (int i = 1; i <= n; ++i)
		if (i != s)
			ans = (ans+max_mid[i])%mod;
}

void solve() {
	clear();
	init();
	for (int i = 1; i <= n; ++i) {
		dij(i);
		count(i);
	}
	printf("%I64d\n",ans);
}

int main()
{
	int t;
	n = m = 0;
	scanf("%d",&t);
	while (t--) solve();
	return 0;
}