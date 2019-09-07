#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll kMod = 998244353;

vector<int> phi;
vector<ll> pow2,f,sf;

// 计算1--n的所有phi(i) 线性时空复杂度，n应该最大是1e7级别的
void get_all_phi(int n, vector<int>& phi) {
	phi.resize(n + 1);
	vector<bool> is_prime(n + 1, true);
	vector<int> prime;
	is_prime[1] = is_prime[0] = false;
	phi[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (is_prime[i]) {
			prime.push_back(i);
			phi[i] = i - 1;
		}
		for (auto p : prime) {
			if (i * p > n) break;
			is_prime[i * p] = false;
			if (i % p) {
				// i不具有素因子p，i*p对于素因子p来讲次数=1。贡献是(p-1)
				phi[i * p] = phi[i] * (p - 1);
			} else {
				phi[i * p] = phi[i] * p;  // i具有素因子p,则i*p对于欧拉函数值来讲乘以p
				break;  // 保证每个数只被最小素因子访问到。
			}
		}
	}
}

// 时间复杂度sqrt(n)求phi(n) n最大1e12-1e14的级别
// more beautiful version, but slower (just a little bit)
ll get_phi(ll n) {
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


void get_all_pow2(int n) {
	pow2.resize(n+1);
	pow2[0] = 1%kMod;
	for (int i = 1; i <= n; ++i)
		pow2[i] = (pow2[i-1]*2)%kMod;
}

void get_all_f_and_sf(int n) {
	f.resize(n+1);
	sf.resize(n+1);
	sf[0] = 0;
	for (int i = 1; i <= n; ++i) {
		ll t = phi[i];
		f[i] = (pow2[t]*t)%kMod;
		sf[i] = (sf[i-1]+f[i])%kMod;
	}
}

int main()
{
	int n = 20;
	get_all_phi(n, phi);
	get_all_pow2(n);
	get_all_f_and_sf(n);
	for (int i = 1; i <= n; ++i)
		printf("phi(%d) %d\n", i, phi[i]);
	int k;
	while (cin>>k) {
		printf("phi(%d) %d\n", k, get_phi(k));
	}
}