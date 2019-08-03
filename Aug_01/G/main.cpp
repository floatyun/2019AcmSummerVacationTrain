#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int kMaxN = 3000;
const int kMod = 998244353;
string s,t;
int l_s,l_t;
int C[kMaxN+2][kMaxN+2];
int SC[kMaxN+2][kMaxN+2];
int F[kMaxN+2][kMaxN+2];
int SF[kMaxN+2][kMaxN+2];
int Tp[kMaxN+2];

void get_C() {
    int n = kMaxN+1;
    memset(C,0,sizeof(C));
    memset(SC,0,sizeof(SC));
    C[0][0] = 1; SC[0][0] = 1;
    C[1][0] = C[1][1] = 1;
    SC[1][0] = 1;
    SC[1][1] = 2;
    for (int i = 2; i < n; ++i) {
        C[i][0] = 1; SC[i][0] = 1;
        for (int j = 1;j <= i; ++j) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1])%kMod;
            SC[i][j] = (SC[i][j-1]+C[i][j])%kMod;
        }
    }
}

void get_Tp() {
    int n = kMaxN+1;
    Tp[0] = 1;
    for (int i = 1; i < n; ++i)
        Tp[i] = (Tp[i-1]*2)%kMod;
}

void reverse(string&s,int l) {
    for (int i = 0, j = l-1; i < j; ++i, --j)
        swap(s[i],s[j]);
}

int get_prezero() {
    int ans = 0;
    for (int i = 0;i < l_s; ++i)
        if (s[i] == '0')
            ans = (ans+Tp[i])%kMod;
    return ans;
}

// not empty seq
int get_no_prezero_and_len_less_than_t_seq() {
    if (l_t <= 1) return 0;
    int ans = s[0] == '0' ? 0 : 1;
    for (int i = 1;i < l_s; ++i) {
        if (s[i] != '0')
            ans = (ans + SC[i][min(i, l_t-2)]) % kMod;
    }
    return ans;
}



void work()
{
    cin>>l_s>>l_t;
    cin>>s; reverse(s, l_s);
    cin>>t; reverse(t, l_t);
    int prezero_seq = get_prezero();
    int no_prezero_and_len_less_than_t_seq = get_no_prezero_and_len_less_than_t_seq();
    F[0][0] = (s[0] <= t[0]) ? 1 : 0;
    SF[0][0] = F[0][0];
//    for (int j = 1;j < l_t; ++j) {
//        F[0][j] = 0;
//        SF[0][j] = SF[0][j - 1];
//   }
    SF[0][1] = 0;
    for (int i = 1; i < l_s; ++i) {
        F[i][0] = (s[i] <= t[0]) ? 1: 0;
        SF[i][0] = (SF[i-1][0] + F[i][0])%kMod;
        //cout<<"("<<i<<", "<<0<<") F,SF ...."<<F[i][0]<<"       "<<SF[i][0]<<endl;
        for (int j = 1; j <= i; ++j) {
            if (s[i] < t[j]) {
                F[i][j] = C[i][j];
            } else if (s[i] == t[j]){
                F[i][j] = SF[i-1][j-1];
            } else {
                F[i][j] = 0;
            }
            SF[i][j] = (SF[i-1][j]+F[i][j])%kMod;
            //cout<<"("<<i<<", "<<j<<") F,SF ...."<<F[i][j]<<"       "<<SF[i][j]<<endl;
        }
        SF[i][i+1] = 0;
    }
    int no_prezero_leq_t_and_l_t_bit_seq = 0;
    for (int i = l_t-1;i < l_s; ++i)
        if (s[i] != '0')
            no_prezero_leq_t_and_l_t_bit_seq = (no_prezero_leq_t_and_l_t_bit_seq+F[i][l_t-1])%kMod;
    int all_seq = Tp[l_s];
    int ans = 1; // 空串
   // cout<<"all seq="<< all_seq<<endl;
    //cout<<"无前导零，长度为l_t,小于等于"<<no_prezero_leq_t_and_l_t_bit_seq<<endl;
    //cout<<"前导零"<<prezero_seq<<endl;
    //cout<<"无前导零，长度小于t"<<no_prezero_and_len_less_than_t_seq<<endl;
    ans = (ans+no_prezero_and_len_less_than_t_seq)%kMod;
    ans = (ans+no_prezero_leq_t_and_l_t_bit_seq)%kMod;
    ans = (ans+prezero_seq)%kMod;
    // no_prezero_and_l_t_bit_seq_and_gt_than_t ---> output ans1
    // no_prezero_and_longer_than_t   ---> output ans2
    ans = ((all_seq-ans)%kMod+kMod)%kMod;
    cout<<ans<<endl;
    //cout<<"end"<<endl;
}

int main() {
    int t;
    get_C();
    get_Tp();
    cin>>t;
    while (t--) work();
    return 0;
    return 0;
}