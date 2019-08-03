#include <bits/stdc++.h>
using namespace std;
const int kMaxN = 1005;
const int kMaxM = 1005;
typedef long long ll;
struct nd {
  int l, r;
  int min_id;
} segTree[kMaxN][kMaxM * 4];
ll segTreeSrcData[kMaxN][kMaxM];
int cost[kMaxN][kMaxM];
ll d[kMaxM];
ll sum_d[kMaxM];
ll sum_li_cost[kMaxM]; // 所有科技点到i等级的花费
ll ans;
int n, m;

void push_up(int ti, int i);

void build(int ti, int i, int l, int r) {
  segTree[ti][i].l = l;
  segTree[ti][i].r = r;
  if (l == r) {
    segTree[ti][i].min_id = l;
    return;
  }
  int mid = (l + r) / 2;
  build(ti, i << 1, l, mid);
  build(ti, (i << 1) | 1, mid + 1, r);
  push_up(ti, i);
}
void push_up(int ti, int i) {
  auto l_id = segTree[ti][i << 1].min_id;
  auto r_id = segTree[ti][(i << 1) | 1].min_id;
  if (segTreeSrcData[ti][l_id] <= segTreeSrcData[ti][r_id])
    segTree[ti][i].min_id = l_id;
  else
    segTree[ti][i].min_id = r_id;
}
int query(int ti, int i, int l, int r) {
  if (segTree[ti][i].l == l && segTree[ti][i].r == r)
    return segTree[ti][i].min_id;
  int mid = (segTree[ti][i].l + segTree[ti][i].r) / 2;
  if (r <= mid)
    return query(ti, i << 1, l, r);
  else if (l > mid)
    return query(ti, (i << 1) | 1, l, r);
  auto l_id = query(ti, i << 1, l, mid);
  auto r_id = query(ti, (i << 1) | 1, mid + 1, r);
  if (segTreeSrcData[ti][l_id] <= segTreeSrcData[ti][r_id])
    return l_id;
  else
    return r_id;
}

void work(int cid) {
  cin >> n >> m;
  auto &sum_cost = segTreeSrcData;
	memset(sum_li_cost, 0, sizeof(sum_li_cost));
  for (int i = 0; i < n; ++i) {
    sum_cost[i][0] = cost[i][0] = 0;
    for (int j = 1; j <= m; ++j) {
      cin >> cost[i][j];
      sum_cost[i][j] = sum_cost[i][j - 1] + (ll)cost[i][j];
			sum_li_cost[j] += cost[i][j];
    }
  }
	// now sum_li_cost[j]表示所有科技从j-1点到j的所有花费
	// 我们要处理成从0点到j的所有花费，求前缀和即可
	for (int j = 1; j <= m; ++j)
		sum_li_cost[j] = sum_li_cost[j-1] + sum_li_cost[j];
  sum_d[0] = d[0] = 0;
  for (int j = 1; j <= m; ++j) {
    cin >> d[j];
    sum_d[j] = sum_d[j - 1] + d[j];
  }
  for (int ti = 0; ti < n; ++ti) build(ti, 1, 0, m);
  ans = 0;
  ll profit;
  for (int x = 0; x <= m; ++x) {
    bool is_stay_at_x = false;
    ll change_cost;
    ll max_change_cost;
    profit = sum_d[x] - sum_li_cost[x];
		// cout<<"_____________________"<<endl;
		// cout<<"sum_d["<<x<<"]:"<<profit<<endl;
    for (int ti = 0; ti < n; ++ti) {
      auto y = query(ti, 1, x, m);
      is_stay_at_x = is_stay_at_x || x == y;
      change_cost = sum_cost[ti][y] - sum_cost[ti][x];
      max_change_cost = ti ? max(max_change_cost, change_cost) : change_cost;
			// cout<<"(ti,y)="<<ti<<","<<y<<"\t"<<change_cost<<endl;
      profit -= change_cost;
    }
		// cout<<"x,max_change_cost"<<x<<","<<max_change_cost<<endl;
    if (!is_stay_at_x)  // 所有科技都升级了，高于x级了，把升级耗费最大的取消升级
      profit += max_change_cost;
		// cout<<"profit,ans"<<profit<<","<<ans<<endl;
		// cout<<"_____________________***************"<<endl;
		ans = max(ans, profit);
  }
	cout<<"Case #"<<cid<<": "<<ans<<endl;
}

int main() {
  int t;
  cin >> t;
  for (int i = 1; i <= t; ++i)
		work(i);
  return 0;
}