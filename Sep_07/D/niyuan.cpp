#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
// 求解不定方程ax+by=(a,b)的一组特解并返回a,b最大公约数
// x,y存储返回的一组特解。易懂version
ll ex_gcd1(ll a, ll b, ll &x, ll &y) {
	if (b) {
		auto d = ex_gcd1(b, a%b, x,  y);
		auto x_bac = x;
		x = y; // x设为后
		y = x_bac - a/b * y; // y设为前-a/b*后
		return d;
	} else {
		x = 1; y = 0;
		return a;
	}
}

// 求解不定方程ax+by=(a,b)的一组特解并返回a,b最大公约数
// x,y存储返回的一组特解。
ll ex_gcd(ll a, ll b, ll &x, ll &y) {
	if (b) {
		auto d = ex_gcd(b, a%b, y, x); // 注意x和y位置互换了。
		// x是后，无需赋值，y是 前-a/b*后 即 y -= a/b*x
		y -= a/b*x;
		return d;
	} else {
		x = 1; y = 0;
		return a;
	}
}

// 求解不定方程ax+by=c.
// 返回值表示是否有解
// d存储是(a,b)
// 当有解的情况下
// x,y存储一组特解,并且确保x是最小的非负整数。
// 通解是X=x+(b/d)*t,Y=y-(a/d)*t t是整数。
bool binary_linear_indefinite_equation(ll a, ll b, ll c, ll &x, ll &y, ll &d) {
	d = ex_gcd(a, b, x, y); // solve: ax+by=(a,b)
	if (c%d) return false;
	x *= c/d;
	y *= c/d;
	auto k = b/d;
	x = (x%k+k)%k; // 调为最小非负整数
	y = (d-a*x)/b;
	return true;
}

// 线性同余方程 Linear congruence equation
// ax = c (mod m) <===> ax+my=c
// x存储最小非负解，通解X=x+kt t为整数
// 有解的情况下，最小非负解x肯定在[0,m)范围内
bool linear_congruence_equation(ll a, ll c, ll m, ll &x, ll &k) {
	ll y, d;
	auto ans = binary_linear_indefinite_equation(a, m, c, x, y, d);
	k = m/d;
	return ans;
}

// 求a在Zm<+,*>中的乘法逆元x
// 返回逆元是否存在,x存储逆元
// ax = 1 (mod m)
bool multiplicative_inverse(ll a, ll m, ll &x) {
	ll k;
	return linear_congruence_equation(a, 1, m, x, k);
	// assert(k == m);
}

// 线性同余方程组 Linear congruence equations
// a_ix = c_i (mod m_i) 共n个
// 可能存在的问题，由于迭代过程中k一直在求最小公倍数，所以可能会爆long long，这个，最佳的方法是直接暴力把ll的定义改为__int128
// 但是要注意__int128的输入输出
// 如果还是爆，我没法子了
bool linear_congruence_equations(int n, ll a[], ll c[], ll m[], ll &x, ll &k) {
	ll x_i, k_i, t, t_i, d;
	x = 0; k = 1;
	for (int i = 0; i < n; ++i) {
		if (!linear_congruence_equation(a[i], c[i], m[i], x_i, k_i))
			return false; 
		// kt+x
		// k_it_i+x_i
		if (!binary_linear_indefinite_equation(
			k, k_i, x_i-x, t, t_i, d))
			return false;
		x += k*t;
		k *= k_i/d;
	}
	return true;
}

int main()
{
	
}