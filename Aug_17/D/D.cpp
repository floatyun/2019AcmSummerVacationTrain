#include <bits/stdc++.h>
using namespace std;
typedef __int128 ll;
typedef __int128 LL;
const LL N=11000;
long long ina[N],inb[N];
ll a[N], b[N];
LL tx,ty;

LL exgcd(LL aa,LL bb)
{
    if(bb==0) {tx=1,ty=0;return aa;}
    LL d=exgcd(bb,aa%bb);
    LL x=ty,y=tx-(aa/bb)*ty;
    tx=x;ty=y;
    return d;
}

LL lcu(LL aa,LL bb)
{
    LL d=exgcd(aa,bb);
    return aa*bb/d;
}

ll solve(ll n, ll m) {
	LL a1,b1,x;
	bool bk=1;
	for(LL i=1;i<=n;i++) {
			scanf("%lld%lld",&ina[i],&inb[i]);
			a[i] = ina[i]; b[i] = inb[i];
	}
	LL A=a[1],B=a[2],C=b[2]-b[1];
	LL g=exgcd(A,B);
	if(C%g) bk=0; 
	else {
			x=((tx*C/g)%(B/g)+(B/g))%(B/g);
			b1=a[1]*x+b[1];
			a1=lcu(a[1],a[2]);
	}
	for(LL i=3;i<=n;i++)
	{
			A=a1,B=a[i],C=b[i]-b1;
			g=exgcd(A,B);
			if(C%g) {bk=0;break;}
			x=((tx*C/g)%(B/g)+(B/g))%(B/g);
			b1=a1*x+b1;
			a1=lcu(a1,a[i]);
	}
	if(bk) return b1; else return -1;
}

int main()
{
    
		long long m, n;
		scanf("%lld", &n);
		scanf("%lld", &m);
    long long cnt = (long long)solve(n, m);
		if (cnt == -1) {
			puts("he was definitely lying");
		} else if (cnt > m) {
			puts("he was probably lying");
		} else {
			printf("%lld\n", cnt);
		}
    return 0;
}