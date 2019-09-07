#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 时间复杂度sqrt(n)求phi(n) n最大1e12-1e14的级别
// more beautiful version, but slower (just a little bit)
ll phi(ll n) {
	ll a = n;
	for (ll p = 2; p * p <= n; ++p)
		if (!(n % p)) {
			do
				n /= p;
			while (!(n % p));
			a = a / p * (p - 1);
		}
	if (n > 1) a = a / n * (n - 1);  // the rest n is a prime
	return a;
}

ll quick_power_mod(ll a,ll b,ll m)
{
		if (b == 0) return 1%m;
    ll ans = 1;
    while(b)//用一个循环从右到左便利b的所有二进制位
    {
        if(b&1)//判断此时b[i]的二进制位是否为1
        {
            ans = (ans*a)%m;//乘到结果上，这里a是a^(2^i)%m
            b--;//把该为变0
        }
        b/=2;
        a = a*a%m;
    }
    return ans;
}

bool is_less(ll a, ll k, ll b) {
	// k个a的那个形式的式子是否小于b
	if (b == 1) {return false;}
	if (k == 1) {
		return a < b;
	} else {
		return is_less(a, k-1, ll(
				ceil(log(b)/log(a))
			)
		);
	}
}

ll cal(ll a, ll b, ll m) {
	if (m == 1) return 0;
	if (b == 1) return a%m;
	auto p = phi(m);
	auto t = cal(a, b-1, p);
	// a^(t+p)%m
	if (is_less(a,b-1,p))
		return quick_power_mod(a,t, m);
	else
		return quick_power_mod(a,t+p, m);
}

ll solve() {
	ll a,b,m;
	scanf("%lld%lld%lld",&a,&b,&m);
	//a%= m;
	if (b == 0) return 1%m;
	return cal(a,b,m);
}

int main()
{
	int t;
	scanf("%d",&t);
	for (int ti = 1; ti <= t; ++ti) printf("%lld\n",solve());
	//cout<<phi(100)<<endl;
	//cout<<quick_power_mod(4,44,100)<<endl;
}