#include <bits/stdc++.h>
using namespace std;

int c[]={1,0,0,0,1,0,1,0,2,1};

int f(int x) {
    int ans = 0;
    while (x) {
        ans += c[x%10];
        x /= 10;
    }
    return ans;
}

int g(int k, int x) {
    if (x <= 1)
        return x^(k&1);
    x = f(x);
    if (k == 1)
        return x;
    return g(k-1, x);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while (t--) {
        int x, k;
        cin>>x>>k;
        if (k)
            cout<<g(k,x)<<"\n";
        else
            cout<<x<<"\n";
    }
    return 0;
}