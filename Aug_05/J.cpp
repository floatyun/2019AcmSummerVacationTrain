#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
    int n, m;
    cin >> n >> m;
    vector<int>books(n);
    int zero_cnt = 0;
    for (auto &b : books) {
        cin>>b;
        if (!b) ++zero_cnt;
    }
    if (m > n || zero_cnt > m) {
        cout << "Impossible\n";
        return;
    }
    if (m == n) {
        cout << "Richman\n";
        return;
    }
    ll ans = 0;
    int i = 0;
    int not_free_cnt = 0;
    while (not_free_cnt < m-zero_cnt) {
        ans += books[i];
        if (books[i]) ++not_free_cnt;
        ++i;
    }
    int min_price = 0x7fffffff;
    for (;i < n; ++i)
        if (books[i])
            min_price = min(min_price, books[i]);
    if (0x7fffffff != min_price)
        ans += min_price-1;
    cout<<ans<<"\n";
}

int main() {
    int t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--)
        solve();
    return 0;
}