#include <bits/stdc++.h>
using namespace std;
//#define debugmode
typedef long long ll;
const ll kMaxLength=1e5+5;
const ll mod = 1e9+7;
const ll kp = 26;
const ll inv_kp = 576923081;
vector<ll>t_hash(kMaxLength),s_hash(kMaxLength),kp_pow(kMaxLength),inv_pow(kMaxLength);
ll t_len,s_len;
void prepare() {
	kp_pow[0] = 1; inv_pow[0] = 1;
	for (ll i = 1; i < kMaxLength; ++i) {
		kp_pow[i] = (ll)kp_pow[i-1]*(ll)kp%mod;
		inv_pow[i] = (ll)inv_pow[i-1]*(ll)inv_kp%mod;
	}
}
void cal_hash(string&s, vector<ll>&sh, ll len) {
	for (ll i = 0; i < len; ++i)
		sh[i] = (ll)kp_pow[i]*(ll)(s[i]-'a')%mod;
}

// [l,r)
ll get_hash(ll l, ll r, vector<ll>&h) {
	if (l) {
		ll t = h[r-1]-h[l-1];
		t = (t%mod+mod)%mod;
		t = (t*inv_pow[l])%mod;
		return t;
	} else {
		return h[r-1];
	}
}

char pre_ans[3][2][20] = {
	"my child!\n", "oh, child!\n",
	"my teacher!\n","senior!\n",
	"jntm!\n","friend!\n"
};

bool is_substr(vector<ll>&h, ll len, ll val, ll tl, string&a, string&b) {
	ll tval;
	for (ll i = 0; i+tl<=len; ++i) {
		tval = get_hash(i,i+tl,h);
		if (tval == val) {
			bool flag = true;
			for (int j = i; flag && j < i+tl; ++j)
				if (a[j] != b[j-i]) flag = false;
			if (flag) return true;
		}
	}
	return false;
}

string T;
string s;
void solve() {
	cin>>s;
	s_len = s.length();
	cal_hash(s,s_hash,t_len);
	ll c1;
	bool c2;
	if (t_len > s_len) {
		c1 = 0;
		c2 = is_substr(t_hash,t_len,s_hash[s_len-1],s_len,T,s);
	} else if (t_len < s_len) {
		c1 = 1;
		c2 = is_substr(s_hash,s_len,t_hash[t_len-1],t_len,s,T);
	} else {
		c1 = 2;
		c2 = t_hash[t_len-1] == s_hash[s_len-1];
	}
	c2 = !c2;
	cout<<pre_ans[c1][c2];
}

int main()
{
	cin>>T;
	t_len = T.length();
	prepare();
	cal_hash(T,t_hash,t_len);
	ll q;
	scanf("%d",&q);
	while (q--) solve();
}