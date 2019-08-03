#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
ll x[2];
ll a,b;
ll mod;
string n_str;

struct mat{
    ll a[2][2];
    // 初始化默认为单位矩阵
    mat() {
        a[0][0] = 1; a[0][1] = 0;
        a[1][0] = 0; a[1][1] = 1;
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
        for (int i = l-1; i >= 0; --i)
            __val[l-1-i] = s[i]-'0';
    }
    // 余数通过返回值返回，整除结果原地保存
    int div_and_mod_2() {
        int r = 0;
        int t;
        for (auto it = __val.rbegin(); it != __val.rend(); ++it) {
            t = r*10 + *it;
            *it = t>>1;
            r = t&1;
        }
        while (0 == __val.back()) __val.pop_back();
        if (__val.empty()) __val.emplace_back(0);
        return r;
    }
    bool equal_one() {
        return __val.size() == 1 && __val[0] == 1;
    }

    bool equal_zero() {
        return __val.size() == 1 && __val[0] == 0;
    }

    bool gt_one() {
        return __val.size() > 1 || __val[0] > 1;
    }
};

mat quick_power(mat &A, big_num&n) {
    mat B; //单位矩阵
    if (n.equal_zero()) return B;
    //if (n.equal_one()) return A;
    while (n.gt_one()) {
        int r = n.div_and_mod_2();
        if (r) B = A*B;
        A = A*A;
    }
    return A*B;
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