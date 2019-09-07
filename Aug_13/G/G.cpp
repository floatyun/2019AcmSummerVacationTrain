#include <bits/stdc++.h>
using namespace std;

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

int main()
{
	uint64_t sum = 0llu;
	int n;
	cin>>n;
	vector<int>phi;
	get_all_phi(n,phi);
	for (int i = 2; i <= n; ++i)
		sum += phi[i];
	cout<<sum<<endl;
	return 0;
}