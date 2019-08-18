#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int kMaxPointCount = 1024;

namespace lsq {
	const double eps = 1e-10;  //极小值

	//取符号
	int dcmp(double x) {
		if (fabs(x) < eps) return 0;
		return x < 0 ? -1 : 1;
	}

	//点定义
	struct Point {
		double x, y;
		Point(double x = 0, double y = 0) : x(x), y(y) {}
	};

	//向量定义
	typedef Point Vector;
	Vector operator+(const Vector& A, const Vector& B) {
		return Vector(A.x + B.x, A.y + B.y);
	}
	Vector operator-(const Vector& A, const Vector& B) {
		return Vector(A.x - B.x, A.y - B.y);
	}
	Vector operator*(const Vector& A, double p) { return Vector(A.x * p, A.y * p); }
	Vector operator/(const Vector& A, double p) { return Vector(A.x / p, A.y / p); }
	bool operator<(const Vector& A, const Vector& B) {
		return (A.x < B.x) || ((A.x == B.x) && A.y < B.y);
	}
	bool operator==(const Vector& A, const Vector& B) {
		return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
	}

	// !基本运算
	double Dot(const Vector& A, const Vector& B) {  //点乘
		return A.x * B.x + A.y * B.y;
	}
	double Length(const Vector& A) {  //求长度
		return sqrt(Dot(A, A));
	}
	double Angle(const Vector& A, const Vector& B) {  //求角度
		return acos(Dot(A, B)) / Length(A) / Length(B);
	}
	double Cross(const Vector& A, const Vector& B) {  //点乘
		return A.x * B.y - A.y * B.x;
	}
	double Area2(Point A, Point B, Point C) {  //求三角面积
		return Cross(B - A, C - A);
	}
};  // namespace lsq

namespace lly {
	// 所有下标符合C++风格
	// 奢侈做法：使用全局变量开4倍数组。
	// 最小值，最大值，区间和，区间加相同数模板
	// 考场抄代码所有item_type, sum_type 换成ll即可
	struct segment_tree {
		// 最大的初始数组大小和响应的线段树节点数组最大大小。
		const static int kMaxItemSize = kMaxPointCount*2;
		const static int kMaxSegTreeSize = kMaxItemSize << 2;

		int item_sz;
		int seg_sz;
		int &n = item_sz;
		int &stn = seg_sz;

		typedef ll item_type;
		typedef ll sum_type;

		struct nd {
			int l, r;
			sum_type sm;   // sum flag
			// lazy flags
			item_type all_add;  // lazy标记，表示区间内的数都要加上的数
			// other flags
			inline void add(item_type a) {
				all_add += a;
				sm += (sum_type)(r-l)*a;
			}
			inline int mid() { return l + (r - l) / 2; }
		};

		item_type a[kMaxItemSize];
		nd nds[kMaxSegTreeSize];

		void init(int cnt) {
			n = cnt;
			memset(a, 0, sizeof(a));
			seg_sz = (2 << (int)(ceil( log2(item_sz) ))) - 1;
		}

		inline int parent(int x) { return (x - 1) >> 1; }
		inline int lchild(int x) { return (x << 1) | 1; }
		inline int rchild(int x) { return (x << 1) + 2; }

		inline void build() { build(0, n, 0); }

		inline void set_flags(int root, int i) {  // nds[root]用a[i]设置各类标志
			auto &p = nds[root];
			p.l = i;
			p.r = i + 1;
			p.sm = a[i];
		}

		inline void merge_flags(int root) {
			auto &p = nds[root];
			auto &l = nds[lchild(root)];
			auto &r = nds[rchild(root)];
			p.l = l.l;
			p.r = r.r;
			p.sm = l.sm + r.sm + p.all_add * (sum_type)(p.r - p.l);
		}

		void build(int l, int r, int root) {
			nds[root].all_add = 0;
			if (l + 1 == r) {
				set_flags(root, l);
				return;
			}
			int m = l + (r - l) / 2;
			build(l, m, lchild(root));
			build(m, r, rchild(root));
			merge_flags(root);
		}

		// [l,r)区间的数都加上val
		void add(int l, int r, item_type val, int root = 0) {
			if (l == nds[root].l && r == nds[root].r) {
				nds[root].add(val);
				return;
			}
			int m = nds[root].mid();
			if (r <= m) {  // only left part
				add(l, r, val, lchild(root));
			} else if (l >= m) {  // only right part
				add(l, r, val, rchild(root));
			} else {
				add(l, m, val, lchild(root));
				add(m, r, val, rchild(root));
			}
			merge_flags(root);
		}

		sum_type get_sum(int l, int r, int root = 0) {
			if (l == nds[root].l && r == nds[root].r) {
				return nds[root].sm;
			}
			// 勿忘加上all_add lazy标记
			int m = nds[root].mid();
			ll lazy = nds[root].all_add * (sum_type)(r - l);
			if (r <= m) {  // only left part
				return get_sum(l, r, lchild(root)) + lazy;
			} else if (l >= m) {  // only right part
				return get_sum(l, r, rchild(root)) + lazy;
			} else {
				return get_sum(l, m, lchild(root))    // left
							+ get_sum(m, r, rchild(root))  // right
							+ lazy;
			}
		}
	};
};  // namespace lly

int point_cnt;
typedef lsq::Point point;
typedef point vec;
vector<point> init_p;
struct isodirectional_info {
  int first;  // 包含
  int last;   // 包含
  int cnt;
};

struct anti_info{
	int first;
	int last;
	int cnt;
	int real_vec_id; // 如果实际不存在，则为-1
};

void init() {
  cin >> point_cnt;
  init_p.resize(point_cnt);
  for (auto& p : init_p) cin >> p.x >> p.y;
}

void get_anti_infos(vector<vec>&vecs, int n, vector<isodirectional_info>& infos, vector<anti_info>&anti_infos) {
	int now = 0;
	int anti = 1;
	// auto is_inverse = [](const vec& a, const vec& b) {
  //   return lsq::dcmp(lsq::Cross(a, b)) == 0 && lsq::dcmp(lsq::Dot(a, b)) < 0;
  // };
	anti_infos.clear();
	while (now < n) {
		// find the anti(now)
		vec &now_vec = vecs[infos[now].first];
		bool flag = false;
		for (;anti < now + n; ++anti) {
			// anti 和 now 肯定不同向，所以只需要点积小于（逆时针旋转超过180°）等于（恰好180°）0即可。
			int res = lsq::dcmp(lsq::Cross(now_vec, vecs[infos[anti].first]));
			if (res == 0) {
				anti_infos.emplace_back(anti_info{
					infos[anti].first, // first
					infos[anti].last, // last
					infos[anti].cnt,// cnt
					anti%n// real vec_id
				});
				flag = true;
				break;
			} else if (res < 0) {
				anti_infos.emplace_back(anti_info{
					infos[anti - 1].last + 1, // first
					infos[anti - 1].last, // last
					0, // cnt
					-1 // real_vec_id
				});
				flag = true;
				break;
		  }
	  }
		if (!flag) {
			// 说明枚举范围内的都是小于180°
			anti_infos.emplace_back(anti_info{
				infos[anti - 1].last + 1, // first
				infos[anti - 1].last, // last
				0, // cnt
				-1 // real_vec_id
			});
		}
		++now;
	}
}

lly::segment_tree seg_tr;
ll count_around(point d) {
  // generate vecs
  vector<vec> vecs;
  for (auto& p : init_p)
    if (!(p == d)) vecs.push_back(p - d);
  auto anti_clock_order = [](const point& a, const point& b) {
    return atan2(a.y, a.x) < atan2(b.y, b.x);
  };
  sort(vecs.begin(), vecs.end(), anti_clock_order);  // O(nlnn)
  int n = vecs.size();

	// for (int i = 0; i < n; ++i)
	// 	cout<<"i = "<<i<<"\t "<<vecs[i].x<<", "<<vecs[i].y<<endl;

  // generate vec_id
  vector<int> vec_ids;
  vector<isodirectional_info> isodir_infos;
  int vec_id = -1;

  // 注意a,b 都是非零向量
  auto is_isodirectional = [](const vec& a, const vec& b) {
    return lsq::dcmp(lsq::Cross(a, b)) == 0 && lsq::dcmp(lsq::Dot(a, b)) >= 0;
  };

  for (int i = 0; i < n; ++i)
    if (i && is_isodirectional(vecs[i - 1], vecs[i])) {
      vec_ids.push_back(vec_id);
    } else {
			if (vec_id >= 0) isodir_infos[vec_id].last = i - 1;
      ++vec_id; isodir_infos.emplace_back(isodirectional_info());
      vec_ids.push_back(vec_id);
      isodir_infos[vec_id].first = i;
    }
  if (vec_id >= 0) isodir_infos[vec_id].last = n - 1;
	++vec_id;
  for (auto& x : isodir_infos) x.cnt = x.last - x.first + 1;
  // double copy
  for (int i = 0; i < n; ++i) {
    vecs.push_back(vecs[i]);
    vec_ids.push_back(vec_ids[i] + n);
  }
	for (int i = 0; i < vec_id; ++i)
		isodir_infos.push_back(isodirectional_info{
			isodir_infos[i].first + n,
			isodir_infos[i].last + n,
			isodir_infos[i].cnt
		});

	auto &infos = isodir_infos;

	// string line(80,'_');
	// cout<<line<<endl;
	// for (int i = 0; i < 2*n; ++i)
	// 	cout<<"i = "<<i<<"\t "<<vecs[i].x<<", "<<vecs[i].y<<endl;
	// cout<<line<<endl;
	// for (int i = 0; i < 2*n; ++i)
	// 	cout<<"i = "<<i<<"\t vec_ids[i] = "<<vec_ids[i]<<endl;
	// cout<<line<<endl;
	// for (int i = 0; i < 2*vec_id; ++i)
	//  cout<<"i = "<<i<<"\t infos[i]"<<infos[i].first<<", "<<infos[i].last<<", "<<infos[i].cnt<<endl;

  ll ans = 0;
  // 对每个vec_id产生旋转180° 单个需要O(N)，但是n个可以总体O(n)
	vector<anti_info> anti_infos;
	get_anti_infos(vecs, vec_id, isodir_infos, anti_infos);

	for (int i = 0; i < vec_id; ++i)
		anti_infos.emplace_back(anti_info{
			anti_infos[i].first + n,
			anti_infos[i].last + n,
			anti_infos[i].cnt,
			anti_infos[i].real_vec_id
		});

	// cout<<line<<endl;
	// for (int i = 0; i < 2*vec_id; ++i)
	// 	cout<<"i = "<<i<<"\t anti[i]"<<anti_infos[i].first<<", "<<anti_infos[i].last<<", "<<anti_infos[i].cnt<<endl;


	seg_tr.init(n*2+10);
	seg_tr.build();
	// 枚举vec_id vec_id->vec_id+1
  // 对每个vec_id产生 计算查询的区间的l和r O(1)
		// 查询区间和 O(lnn)，ans+=区间和
		// vec_id--->vec_id时，原来的区间整体减去一个数（可O（1）计算出）
		// 同时下一次的查询区间会变掉，l,r--->l',r' 由于预求的数组可O(1)
		// 需要采用单点更新的方式一个一个把在l',r'区间但不在原本的l,r区间的点的值计算出来
		// 因为前面的种种预处理已经求出的数组的存在，单点值本需要O(n)
		// 但因为预处理的几个数组计算可以O(1)
		// 虽然每次vec_id--->vec_id+1需要进行的单点修改的个数不确定，
		// 但是整体分析知道单点修改次数恰好是O(n)级别，单点修改总复杂度O(nlnn)
	
	int l = 0, r = 0, L, R;
	// int A;
	int B;
	int Aid, Bid;
	int pre_antiA_last;
	bool is_first = true;
	//auto &infos = isodir_infos;
	// ll tmp_val;
	for (Aid = 0; Aid < vec_id; ++Aid) {
		//A = infos[Aid].first;
		L = infos[Aid].last + 1;
		R = anti_infos[Aid].first; // [l,r)--->[l,R)
		if (!is_first) {
			// 原区间集体减去
			// tmp_val = anti_infos[Aid].last - pre_antiA_last;
			// cout<<"minus "<<l<<", "<<r<<"\t"<<tmp_val<<endl;
			if (l < r)
				seg_tr.add(l,r,-(anti_infos[Aid].last - pre_antiA_last));
		}
		// cout<<"Aid= "<<Aid<<endl;
		// cout<<"l,r="<<l<<","<<r<<endl;
		// cout<<"L,R="<<L<<","<<R<<endl;
		// 单点修改增加元素
		for (B = max(L, r); B < R; ++B) {
			// 线段树原始数组a[B]的值，使用单点修改修改即可。
			// 注意a[B]原本肯定是0.所以只需要调用区间集体加函数即可。
			Bid = vec_ids[B];
			// cout<<"B="<<B<<endl;
			// cout<<"Bid="<<Bid<<endl;
			// tmp_val = anti_infos[Bid].first - anti_infos[Aid].last - 1;
			// cout<<" set "<<B<<"\t\t"<<tmp_val<<endl;
			seg_tr.add(
				B,B+1, // 区间[B,B+1)
				anti_infos[Bid].first - anti_infos[Aid].last - 1
			);
		}
		if (L < R) {
			// tmp_val = seg_tr.get_sum(L, R);
			// cout<<"query "<<L<<",   "<<R<<" sum = "<<tmp_val<<endl;
			// cout<<"cnt = "<<infos[Aid].cnt<<endl;
			ans += infos[Aid].cnt*seg_tr.get_sum(L, R);
		}
		l = L; r = R;
		is_first = false;
		pre_antiA_last = anti_infos[Aid].last;
	}
	// cout<<"ans = "<<ans<<endl;
  return ans / 3;  // 每一个ABC-D的flower都会被计数3次
}

int main() {
  init();
  ll ans = 0;
  for (auto d : init_p) ans += count_around(d);  // O(n)
  cout<<ans<<endl;
  return 0;
}