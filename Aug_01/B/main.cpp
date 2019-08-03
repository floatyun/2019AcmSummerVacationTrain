#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll x[2];
ll a,b;
ll mod;
string n_str;

int help[10][4];

struct mat{
    ll a[2][2];
    // 初始化默认为单位矩阵
    mat() {
        a[0][0] = 1ll; a[0][1] = 0ll;
        a[1][0] = 0ll; a[1][1] = 1ll;
    }

    void out() {
        // cout<<a[0][0]<<"\t"<<a[0][1]<<endl;
       //  cout<<a[1][0]<<"\t"<<a[1][1]<<endl;
    }

    mat operator *(mat&sec) {
        mat res;
        for (int i = 0; i < 2; ++i)
            for (int j = 0;j < 2; ++j) {
                ll t = 0;
                for (int k = 0; k < 2; ++k)
                    t = (t+a[i][k]*sec.a[k][j])%mod;
                res.a[i][j] = t;
            }
        return res;
    }
};

struct big_num{
    vector<int>__val;

    big_num(int a = 0){__val.clear();__val.push_back(a);}
    big_num(const string&s) {
        int l = s.length();
        __val.resize(l);
        for (int i = 0;i < l; ++i)
            __val[i] = s[i]-'0';
    }
};

mat quick_power(mat A, int n) {
    mat B;
    if (n == 0) return B;
    while (n > 1) {
        if (n%2 == 1)
            B = A*B;
        A = A*A;
        n /= 2;
    }
    return A*B;
}

mat quick_power(mat A, big_num&n) {
    mat B; //单位矩阵
    mat C;
    if ((n.__val.size() == 1) && (n.__val[0] == 0)) return B;
    while (!n.__val.empty()) {
        int r = n.__val.back();
        n.__val.pop_back();
        C = quick_power(A,r);
        B = B*C;
        A = quick_power(A,10);
    }
    return B;
}


int main() {
    cin>>x[0]>>x[1];
    cin>>a>>b;
    cin>>n_str;
    cin>>mod;
    a%= mod; b %= mod;

    mat A;
    A.a[0][0] = a;  A.a[0][1] = 1;
    A.a[1][0] = b;  A.a[1][1] = 0;

    big_num n(n_str);


    A = quick_power(A, n);
    cout<<((x[1]*A.a[0][1])%mod+(x[0]*A.a[1][1])%mod)%mod<<endl;

    return 0;
}