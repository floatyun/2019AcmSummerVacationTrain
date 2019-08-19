#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// #define debugmode

const int kMaxPointCount = 1024;
const int kMaxPointCount2 = kMaxPointCount*2;
struct nd{
	int l,r;
	ll all_add, sum;
};
nd nds[kMaxPointCount2<<2];
inline int lchild(int x) { return (x << 1) | 1;}

void build(int l,int r,int root = 0) { // 针对本题特殊定制的build
	nds[root].l = l; nds[root].r = r;
	nds[root].all_add = 0; nds[root].sum = 0;
	if (l + 1 == r) return;
	int m = l + (r - l) / 2;
	int lch = lchild(root);
	build(l, m, lch);
	build(m, r, lch+1);
}

void add(int l, int r, ll val, int root = 0) {
	if (l == nds[root].l && r == nds[root].r) {
		nds[root].all_add += val;
		// sum是不考虑自己的以及祖先的all_add的flag情况下的sum
		// 所以这个节点区间集体加的时候不update sum
		return;
	}
	int m = (nds[root].l + nds[root].r)/2;
	int lch = lchild(root);
	if (r <= m) {  // only left part
		add(l, r, val, lch);
	} else if (l >= m) {  // only right part
		add(l, r, val, lch+1);
	} else {
		add(l, m, val, lch);
		add(m, r, val, lch+1);
	}
	// merge_flags
	// sum是不考虑自己的以及祖先的all_add的flag情况下的sum
	nds[root].sum += val * (r-l);
}

ll get_sum(int l, int r, int root = 0) {
	ll base = nds[root].all_add*(r-l); // 求和函数需要把all_add标记考虑到（修正）
	if (l == nds[root].l && r == nds[root].r) {
		return nds[root].sum + base;
	}
	int m = (nds[root].l + nds[root].r)/2;
	int lch = lchild(root);
	if (r <= m) {  // only left part
		return get_sum(l, r, lch) + base;
	} else if (l >= m) {  // only right part
		return get_sum(l, r, lch+1) + base;
	} else {
		return get_sum(l, m, lch) + get_sum(m, r, lch+1) + base;
	}
}
struct point_with_angle;
struct point{
  ll x, y;
	point(){}
	point(ll x, ll y):x(x),y(y) {}
  void set(const point_with_angle& a);
	double operator *(const point&b) const {return (double)x*(double)b.x+(double)y*(double)b.y;} // 向量积，点积
	double operator %(const point&b) const {return (double)x*(double)b.y-(double)y*(double)b.x;} // 叉乘
	point operator -(const point &b) const {return point(x - b.x, y-b.y);}
	point operator +(const point &b) const {return point(x + b.x, y+b.y);}
	bool operator ==(const point&b) const {return x == b.x && y == b.y;}
};
inline int sign(double a) {return abs(a) >= 1e-6 ? (a > 0 ? 1 : -1) : 0;}

struct point_with_angle {
  ll x, y;
  double angle;
  void set(const point& a) {
    x = a.x; y = a.y;
    angle = atan2(y, x);
  }
  bool operator<(point_with_angle& b) const { return angle < b.angle; }
};

void point::set(const point_with_angle& a)  {x = a.x; y = a.y;}

struct info{
	int first,last,cnt;
	info(){}
	void set(int f, int l) {first = f; last = l; cnt = l-f+1;}
};

point inp[kMaxPointCount];
typedef point vec;
point_with_angle sort_p[kMaxPointCount];
vec vecs[kMaxPointCount2];
int vec_to_dir[kMaxPointCount2];
// infos of dir and infos of anti dir
info infos[kMaxPointCount2],antiinfos[kMaxPointCount2];
int pn, vecn, dirn;

void get_vecs(int d) {
	vecn = 0;
	for (int i = 0; i < pn; ++i)
		if (inp[i] == inp[d]) continue;
		else sort_p[vecn++].set(inp[i]-inp[d]);
	sort(sort_p, sort_p+vecn);
	for (int i = 0; i < vecn; ++i)
		vecs[i].set(sort_p[i]);
	for (int i = 0, j = vecn; i < vecn; ++i, ++j)
		vecs[j] = vecs[i];
}

// a,b都是非零向量
bool is_same_dir(const vec&a, const vec&b) { return abs(a%b) < 1e-6 && a*b > 0; }

void get_dir() {
	// 如果和前面的方向相同，那么就应该用前面的dir
	// 否则，应该使用新dir
	dirn = 0;
	for (int i = 0; i < vecn; ++i) {
		if (i && is_same_dir(vecs[i],vecs[i-1])) {
			vec_to_dir[i] = dirn - 1;
		} else {
			++dirn;
			vec_to_dir[i] = dirn - 1;
		}
	}
	for (int i = 0, j = vecn; i < vecn; ++i, ++j)
		vec_to_dir[j] = vec_to_dir[i] + dirn;
}

void get_infos() {
	for (int i = 0, d = -1; i < vecn; ++i) {
		if (vec_to_dir[i] != d) {
			if (d >= 0) infos[d].last = i-1;
			d = vec_to_dir[i];
			infos[d].first = i;
		}
	}
	if (dirn) infos[dirn -1].last = vecn - 1;
	for (int i = 0; i < dirn; ++i) 
		infos[i].cnt = infos[i].last - infos[i].first + 1;
	for (int i = 0, j = dirn; i < dirn; ++i, ++j)
		infos[j].set(infos[i].first + vecn, infos[i].last + vecn);
}

void get_antiinfos() {
	// j应该在anti(i)的位置停下，如果有的话。如果没有的话，
	// 那么它停在的是逆时针旋转超过180°的第一个存在的vec
	// j的探查范围开始是i后一个方向 止于i旋转一圈的方向i+dirn（不含）
	// 因为判断逆时针旋转度数只是单纯的使用叉乘
	// 叉乘为0视作旋转180°，＜0旋转小于180°，>0旋转大于180°
	// 如果不对j做限定，将会同一个方向视作旋转180°
	int i,j;
	int res;
	for (i = 0, j = 0; i < dirn; ++i) {
		for (j = max(j, i+1); j < i + dirn; ++j) {
			res = sign(vecs[infos[i].first]%vecs[infos[j].first]);
			if (res == 0) { // = 180°
				antiinfos[i].set(infos[j].first, infos[j].last);
				break;
			} else if (res < 0) { // > 180°
				antiinfos[i].set(infos[j].first, infos[j].first -1);
				break;
			}
		}
		if (j == i + dirn) {
			antiinfos[i].set(infos[j].first, infos[j].first -1); // 360°
		}
	}
	for (int i = 0, j = dirn; i < dirn; ++i, ++j)
		antiinfos[j].set(antiinfos[i].first + vecn, antiinfos[i].last + vecn);
}

ll solve() {
	ll ans = 0;
	int dA, dB;
	int B;
	int l = 0, r = 0, L, R;
	bool need_work;
	ll tmp_val;
	build(0, 2 * vecn);
	for (dA = 0; dA < dirn; ++dA) {
		L = infos[dA].last + 1;
		R = antiinfos[dA].first;
		need_work = L < R;
		if (need_work && L < r) {
			// 区间集体减
			// assert(dA);
			tmp_val = antiinfos[dA].last - antiinfos[dA-1].last;
			assert(tmp_val>=0);
			add(L, r, -tmp_val);
		}
		for (B = max(L, r); B < R; B = infos[dB].last + 1) {
			dB = vec_to_dir[B];
			add(B, infos[dB].last + 1, 
				antiinfos[dB].first - antiinfos[dA].last - 1);
		}
		if (need_work) {
			tmp_val = get_sum(L, R);
			ans += infos[dA].cnt * tmp_val;
		}
		l = L; r = R;
	}
	return ans;
}

int main() {
	cin>>pn;
	for (int i = 0; i < pn; ++i)
		scanf("%lld%lld",&inp[i].x, &inp[i].y);
	ll ans = 0;
	for (int d = 0; d < pn; ++d) {
		get_vecs(d);
		get_dir();
		get_infos();
		//if (dirn < 3) continue;
		get_antiinfos();
		ans += solve();
	}
	cout<<ans/3<<endl;
	return 0;
}