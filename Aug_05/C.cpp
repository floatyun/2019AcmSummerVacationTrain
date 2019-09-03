#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll solve()
{
    int n;
    string a,b,c;
    cin>>n;
    cin>>a>>b;
    for (int i = 0; i < n; ++i)
        c += (a[i] == b[i] ? '0' : '1');
    int diff_seg_cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (c[i] == '0') continue;
        if (0 == i || c[i-1] == '0')
            ++diff_seg_cnt;
    }
    if (diff_seg_cnt > 2)
        return 0ll;
    else if (diff_seg_cnt == 2)
        return 6ll;
    else if (diff_seg_cnt == 1)
        return 2ll*(n-1);
    else
        return (ll)n*(ll)(n+1)/2ll;
}

int main()
{
    int t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> t;
    while (t--)
        cout<<solve()<<"\n";
    return 0;
}