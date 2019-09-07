#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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

// m两两互质
// 当模数是long long的时候，两个数相乘要用__int128
// 当模数是__int128的时候，使用ex_gcd解线性同余方程组或者使用快速模乘防止爆__int128
bool chinese_remainder_theory(int n, ll c[], ll m[], ll &x, ll &k) {
	ll &M = k;
	ll Mi, inv_Mi;
	__int128 t;
	M = 1; x = 0;
	for (int i= 0; i < n; ++i) M *= m[i];
	for (int i = 0; i < n; ++i) {
		Mi = M/m[i];
		multiplicative_inverse(Mi,m[i],inv_Mi); // 肯定存在
		t = c[i]%M;
		t = t*Mi%M;
		t = t*inv_Mi%M; // 防止爆long long
		x = (x+(ll)t)%M;
	}
	return true;
}

const int kMaxN = 20;
ll c[kMaxN],m[kMaxN];
int main()
{
	int n;
	scanf("%d",&n);
	for (int i = 0; i < n; ++i) scanf("%lld",c+i);
	for (int i = 0; i < n; ++i) scanf("%lld",m+i);
	//for (int i = 0; i < n; ++i) c[i] = (c[i]%m[i]+m[i])%m[i];
	ll ans, k;
	chinese_remainder_theory(n,c,m,ans,k);
	printf("%lld\n",ans);
	return 0;
}