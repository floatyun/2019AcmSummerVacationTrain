#include <algorithm>
#include <cstring>
#include <iostream>
#include <stack>
#include <vector>
using namespace std;
#define lc o * 2
#define rc o * 2 + 1
vector<pair<int, int> > Vec[1610000];
int n, m;
int ql, qr;
int Tsize;
int ans = 0;
int T[410000];
int fa[410000];
int heigh[410000];

int get_Pos(int c) { return lower_bound(T + 1, T + Tsize + 1, c) - T; }

struct edge {
  int u, v;
  int l, r;
  edge(){};
  edge(int tu, int tv, int tl, int tr) : u(tu), v(tv), l(tl), r(tr){};
} Edge[110000];

struct record {
  int u, v, heigh;
  record(int tu, int tv, int th) : u(tu), v(tv), heigh(th){};
};
int FIND(int x) {
  if (x == fa[x])
    return x;
  else
    return FIND(fa[x]);
}

void add(int o, int l, int r, int u, int v) {
  if (ql <= l && r <= qr) {
    Vec[o].push_back(make_pair(u, v));
    return;
  }
  if (l == r) return;
  int mid = (l + r) / 2;
  if (ql <= mid) add(lc, l, mid, u, v);
  if (qr > mid) add(rc, mid + 1, r, u, v);
}

void dfs(int o, int l, int r) {
  stack<int> ST;
  for (int i = 0; i < Vec[o].size(); i++) {
    int u = Vec[o][i].first;
    int v = Vec[o][i].second;
    int fu = FIND(u);
    int fv = FIND(v);
    if (fu == fv) continue;
    if (heigh[fu] < heigh[fv]) swap(fu, fv);  // U 总是高度大的一个
    fa[fv] = fu;                              // V 合并到U上
    ST.push(fv);
    heigh[fu] += heigh[fv];
  }
  bool Rflag = 0;
  if (FIND(1) == FIND(n)) {
    ans += T[r] - T[l] + 1;
    Rflag = 1;
  }
  int mid = (l + r) / 2;
  if (l < r && !Rflag) {
    dfs(lc, l, mid);
    dfs(rc, mid + 1, r);
  }
  while (!ST.empty()) {
    int t = ST.top();
    if (fa[t] == t) continue;
    heigh[fa[t]] -= heigh[t];
    fa[t] = t;
    ST.pop();
  }
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    edge &e = Edge[i];
    scanf("%d%d%d%d", &e.u, &e.v, &e.l, &e.r);
    T[i] = e.l;
    T[i + m] = e.r;
  }
  sort(T + 1, T + 2 * m + 1);
  Tsize = unique(T + 1, T + 2 * m + 1) - T - 1;

  for (int i = 1; i <= n; i++) {
    heigh[i] = 1;
    fa[i] = i;
  }

  for (int i = 1; i <= m; i++) {
    ql = lower_bound(T + 1, T + Tsize + 1, Edge[i].l) - T;
    Edge[i].l = ql;
    qr = lower_bound(T + 1, T + Tsize + 1, Edge[i].r) - T;
    Edge[i].r = qr;
    add(1, 1, Tsize - 1, Edge[i].u, Edge[i].v);
  }
  dfs(1, 1, Tsize - 1);
  cout << ans << endl;
}