// https://nanti.jisuanke.com/t/41355
// lly 因为今天用的是学校电脑的机子，粘贴模板注释都变乱码了 缩进也全被吃了。
// 这份代码是回去之后重新粘贴板子的。
#include <bits/stdc++.h>
using namespace std;
struct mod_sys{
    typedef long long ll;
    ll mod;
    // mod_sys类初始化设置模数
    inline void set_mod(ll mod0) {mod = mod0;}
    // 返回a在[0,mod)内标准等价的数，即数学意义上的a%mod
    inline ll to_std(ll a) {return (a%mod+mod)%mod;}
    // 计算数学意义上的a*n%mod
    ll mlt(ll a, ll n) {
        a = to_std(a); n = to_std(n);
        if (0 == a || 0 == n) return 0;
        // 始终维持要求的数可以表示为n(a)+t
        ll t = 0;
        while (n > 1) {
            if (n&1) t = (t+a)%mod;
            n >>= 1; a = (a<<1)%mod;
        }
        return (a+t)%mod; // now n = 1
    }
    // 计算数学意义上的a^n%mod 输入应当a,n>=0
    ll pow(ll a, ll n)
    {   
        if (n == 0) return 1%mod;
        a = to_std(a);
        // 始终维持要求的数可以表示为(a)^n*t
        ll t = 1;
        while (n > 1)
        {
            if (n&1) t = t*a%mod;
            n >>= 1; a = a*a%mod;
        }
        return a*t%mod; // now n = 1
    }
    // 计算数学意义上的a^n%mod 输入应当a,n>=0
    // 此版本使用quick_mlt防止相乘爆ll
    ll pow_v2(ll a, ll n)
    {   
        if (n == 0) return 1%mod;
        a = to_std(a);
        // 始终维持要求的数可以表示为(a)^n*t
        ll t = 1;
        while (n > 1)
        {
            if (n&1) t = mlt(t,a);
            n >>= 1; a = mlt(a,a);
        }
        return mlt(t,a); // now n = 1
    }
};
typedef long long ll;
// 除非是设置单位矩阵，否则必须调用set_size进行设置大小并清零（或指定值)的初始化
// 所有函数都预设传入了正确的参数
// 矩阵乘法使用取模版，加减数乘未取模(默认它们不爆) 因为一般题目也没这些操作
struct mtr{
    int r_sz, c_sz;
    typedef ll item_type;
    typedef vector<item_type> row_type;
    vector<row_type> data;
    mtr():r_sz(0),c_sz(0),data(){}
    // 设置大小，并且全部元素设置为item_val值
    void set_size(int r_size, int c_size, int item_val = 0) { 
        r_sz = r_size; c_sz = c_size;
        data.resize(r_sz);
        for (auto &row : data)
            row.resize(c_sz, item_val);
    }

    inline bool is_square() { return r_sz == c_sz; }

    // inline row_type& operator()(int r) { return data[r]; }
    // inline item_type& operator()(int r,int c) { return data[r][c];}

    // 会自动调用set_size,调用之前请勿调用set_size
    // 设置成n阶单位矩阵
    void set_identity(int n) {
        set_size(n, n, 0);
        for (int i = 0; i < n; ++i)
            data[i][i] = 1;
    }
    void in() {
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j)
                scanf("%lld", &data[i][j]);
    }
    // 矩阵输出，主要为了调试
    void out() {
        for (auto &row : data) {
            for (auto &cell : row)
                cout<<cell<<" ";
            cout<<"\n";
        }
    }
    // 矩阵加，假设传参合法
    mtr operator+(const mtr& obj) const {
        mtr ans;
        ans.set_size(r_sz, c_sz);
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j)
                ans.data[i][j] = data[i][j] + obj.data[i][j];
        return ans;
    }
    mtr operator-(const mtr& obj) const {
        mtr ans;
        ans.set_size(r_sz, c_sz);
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j)
                ans.data[i][j] = data[i][j] - obj.data[i][j];
        return ans;
    }
    // 矩阵数乘 数在右边
    // 数乘 数在左边必须在类外边用函数实现，模板不提供，容易改出来
    mtr operator*(item_type obj) const {
        mtr ans;
        ans.set_size(r_sz, c_sz);
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j)
                ans.data[i][j] = data[i][j] * obj;
        return ans;
    }
    // 所有元素对mod取模(数学意义)
    void get_mod(ll mod) {
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < c_sz; ++j) {
                data[i][j] %= mod;
                if (data[i][j] < 0)
                    data[i][j] += mod;
            }
    }
    // 矩阵乘法 不用运算符乘号进行重载，便于增加mod参数修改成取模版
    // 默认元素乘法不爆long long，否则需要引入mod_sys模板
    // 默认待两个输入矩阵已经get_mod规约过了。
    mtr mlt(const mtr& obj, ll mod) const {
        mtr ans;
        ans.set_size(r_sz, obj.c_sz);
        for (int i = 0; i < r_sz; ++i)
            for (int j = 0; j < obj.c_sz; ++j) {
                item_type t = 0;
                for (int k = 0; k < c_sz; ++k)
                    t = (t+(data[i][k]*obj.data[k][j])%mod)%mod;
                ans.data[i][j] = t;
            }
        return ans;
    }
    // 预设n>=0
    mtr pow(ll n, ll mod) const {
        mtr a = *this;
        mtr t;
        t.set_identity(r_sz);
        // (a)^n*t
        if (n == 0) return t;
        while (n>1) {
            if (n&1) t = a.mlt(t, mod);
            n >>= 1; a = a.mlt(a, mod);
        }
        return a.mlt(t, mod);
    }
};


const ll kMod = 998244353;
mod_sys mod;
mod_sys mod4;
ll inv_4;
map<ll,ll>dic;
mtr A,F;

/*ll cal(ll n) {
	ll ans = mod4.pow(3,n);
	if (n&1) ans = mod4.to_std(ans+1);
	else ans = mod4.to_std(ans-1);
	return ans/4;
}*/

ll cal2(ll n) {
	auto it = dic.find(n);
	if (it != dic.end())
		return dic[n];
	ll ans;
    mtr An = A.pow(n,kMod);
    mtr t = F.mlt(An,kMod);
    ans = t.data[0][1];
	dic[n] = ans;
	return ans;
}

int main()
{
/*	mod.set_mod(kMod);
	inv_4 = mod.pow(4,kMod-2);
	mod4.set_mod(4*kMod);*/
	F.set_size(1,2);
	F.data[0][0] = 1; F.data[0][1] = 0;
	A.set_size(2,2);
    A.data[0][0] = 3; A.data[0][1] = 1;
    A.data[1][0] = 2; A.data[1][1] = 0;
    ll q,n;
    scanf("%lld%lld",&q,&n);
    ll ans;
    ll xor_ans = 0;
    for (ll i = 0; i < q; ++i) {
        ans = cal2(n);
        n ^= (ans*ans);
        xor_ans ^= ans;
    }
    printf("%lld\n",xor_ans);
	return 0;
}