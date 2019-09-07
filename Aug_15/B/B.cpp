#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
#include <cmath>
#include <string>
#include <cstring>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <ctime>
using namespace std;
#define me(x,y) memset(x,y,sizeof x)
#define MIN(x,y) (x) < (y) ? (x) : (y)
#define MAX(x,y) (x) > (y) ? (x) : (y)
#define SGN(x) ((x)>0?1:((x)<0?-1:0))
#define ABS(x) ((x)>0?(x):-(x))

typedef long long ll;
typedef unsigned long long ull;

const int maxn = 1e5+10;
const ll INF = 0x3f3f3f3f;
const int MOD = 1e9+7;
const int eps = 1e-8;

ll qpow(ll a,ll b,ll p){
  ll ans=1;
  while(b){
    if(b&1) ans=ans*a%p;
    a=a*a%p;
    b>>=1;
  }
  return ans;
}
int mod_sqrt(int a,int n){
  int b,k,i,x;
	if (a == 0) {
		return 0;
	}
  if(n==2) return a%n;
  if(qpow(a,(n-1)/2,n) == 1){
    if(n%4 == 3){
      x=qpow(a,(n+1)/4,n);
    }
    else{
      for(b=1; qpow(b,(n-1)/2,n) == 1; b++);
      i = (n-1)/2;
      k=0;
      while(i%2==0){
        i /= 2,k /= 2;
        if((qpow(a,i,n)*qpow(b,k,n)+1)%n == 0) k += (n-1)/2;
      }
      x = qpow(a,(i+1)/2,n)*qpow(b,k/2,n)%n;
    }
    if(x*2 > n) x = n-x;
    return x;
  }
  return -1;
}

int main(){
	int t;
	cin>>t;
	ll p = 1000000007;
	while (t--) {
		ll b, c;
		b %= p; c %= p;
		cin>>b>>c;
		ll a = ((b*b)%p-(4*c)%p+p)%p;
		int u = mod_sqrt(a,p);
		//cout<<u<<endl;
		if (u == -1) {
			cout<<"-1 -1\n";
			continue;
		}
		u %= p;
		if (b%2 != u%2) u = p-u;
		ll x = ((b+u)/2)%p;
		ll y = (b+p-x)%p;
		if (x > y) swap(x,y);
		cout<<x<<" "<<y<<"\n";
	}
  return 0;
}