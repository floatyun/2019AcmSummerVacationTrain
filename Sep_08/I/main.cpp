/* lly and lsq
https://nanti.jisuanke.com/t/41356
考场上最后我们差一点做出来了。
但是，baoli lsq == l的判断写错了，写成==0了
其次，我负责写的，一开始update的后面的是复制后面的代码，a[pos]=v这句话没删掉，导致wa了一次。
还有，lsq的数组的第二维大小多开了一个数量级，导致后面调整为块大小1800的时候，爆内存了。
 */
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>
using namespace std;
//#define debugmode
//const int blk_sz = 1800; // 2^9 /2^9 === youyi 9 wei
//const int sh_cnt = 9;
const int blk_sz = 1800; // 2^9 /2^9 === youyi 9 wei
const int kMaxN = 2e5+5;
int n,m;
int a[kMaxN];
typedef int ll;
inline ll read();
void write(ll a);

int last_blk_id;
const int kCnt = kMaxN/blk_sz+5;
const int kMaxKKK = 1e8;

inline int get_blk_id(int i) {return i/blk_sz;}//{return i>>sh_cnt;}
inline int get_id_in_blk(int i) {return i%blk_sz;}


struct ST_Tree{
	int C[kCnt][kMaxKKK/kCnt+1];
	ST_Tree(){
		memset(C,0,sizeof(C));
	}
	int lowbit(int x){
		return x & -x;
	}
	void update(int ID,int pre,int now,int nxt,int val){
		if(now == pre && now == nxt){
			modify(C[ID],val,1);
			modify(C[ID],pre,1);
			return;
		}
		if(now == pre && now != nxt){
			if(val != nxt)
				modify(C[ID],val,1);
			return;
		}
		if(now != pre && now == nxt){
			if(val != pre)
				modify(C[ID],val,1);
			return;
		}
		if(now != pre && now != nxt){
			modify(C[ID],now,-1);
			if(val != pre && val != nxt)
				modify(C[ID],val,1);
			return;
		}
	}
	void modify(int *c,int pos,int del){
		if(pos == 0) return;
		for(int i = pos;i <= n;i += lowbit(i))
			c[i] += del;
	}
	int query(int ID,int x,int y){
		return mk_q(C[ID],y) - mk_q(C[ID],x - 1);
	}
	int mk_q(int *c,int pos){
		int sum = 0;
		for(int i = pos;i >= 1;i -= lowbit(i))
			sum += c[i];
		return sum;
	}

}ST;


void init()
{
    n = read(); m = read();
    for (int i = 0; i < n; ++i) a[i] = read();
    last_blk_id = get_blk_id(n-1);
}

int baoli(int l,int r,int x,int y) {
    int del = 0;
    for(int i = l;i <= r ;i ++){
        if(i == l && a[i] <= y && a[i] >= x) {
            del ++;
            continue;
        }
        if(a[i] <= y && a[i] >= x){
            if(a[i] != a[i - 1])
                del ++;
        }
    }
    #ifdef debugmode
        printf("baoli %d %d %d %d %d %d\n",bid/blk_sz+1,l+1,r+1,x,y,del);
    #else
    #endif
    return del;
}

int main()
{
    init();
    int o;
    int pos,v;
    int l,r,x,y;
    int pre,now,nxt;
    int bid,id_inb;
    int ans;
    for (int i = 0;i < n; ++i) {
        pos = i;
        bid = get_blk_id(pos);
        id_inb = get_id_in_blk(pos);
        if (bid != last_blk_id) {
            if (0 == id_inb) pre = 0; else pre = a[pos-1];
            if (1+id_inb == blk_sz) nxt = 0; else nxt = a[pos+1];
            now = a[pos];
            ST.update(bid,pre,0,0,a[pos]);
        }
    }
    for (int i = 0; i < m; ++i) {
        o = read();
        if (1 == o) {
            pos = read(); v = read();
            --pos;
            if (a[pos] == v) continue;
            bid = get_blk_id(pos);
            id_inb = get_id_in_blk(pos);
            if (bid != last_blk_id) {
                if (0 == id_inb) pre = 0; else pre = a[pos-1];
                if (1+id_inb == blk_sz) nxt = 0; else nxt = a[pos+1];
                now = a[pos];
                ST.update(bid,pre,now,nxt,v);
                a[pos] = v;
            } else { // zuihou yi kuai teshu chu li
                a[pos] = v;
            }
        } else {
            l = read(); --l;
            r = read(); --r;
            x = read();
            y = read();
            ans = 0;
            int l_bid,r_bid;
            l_bid = get_blk_id(l);
            r_bid = get_blk_id(r);
            // di yi kuai teshu chu li
            int tmp = (l_bid+1)*blk_sz;
            int tt;
            tt = baoli(l,min(tmp-1,r),x,y);
            ans += tt;
            #ifdef debugmode
                printf("pre = %d\n",tt);
            #else
            #endif

            for (int bid = l_bid+1; bid < r_bid; ++bid) {
                int t = ST.query(bid,x,y);
                #ifdef debugmode
                    printf("%d %d\n",bid+1,t);
                #else
                #endif
                pre = bid*blk_sz-1;
                if (pre>=l&&a[pre]==a[pre+1] && a[pre]>=x && a[pre]<=y) --t;
                ans += t;
            }
            if (r_bid != l_bid) {
                // zui hou yi kuai teshu chu li
                tt = baoli(max(l,r_bid*blk_sz),r,x,y);
                ans += tt;
                #ifdef debugmode
                    printf("suc = %d\n",tt);
                #else
                #endif
                pre = r_bid*blk_sz-1;
                if (pre>=l&&a[pre]==a[pre+1]&&a[pre]>=x && a[pre]<=y) --ans;
            }
            write(ans);putchar('\n');
        }
    }
    return 0;
}
/*
6 1
3 3 1 5 6 5
2 1 6 1 5
*/





inline ll read()
{
	ll x = 0;
	bool f = 0;
	char ch = getchar();
	while (ch < '0' || '9' < ch)
		f |= ch == '-', ch = getchar();
	while ('0' <= ch && ch <= '9')
		x = x * 10 + ch - '0', ch = getchar();
	return f ? -x : x;
}

void write(ll a)
{
	if (a < 0)
	{
		putchar('-');
		a = -a;
	}
	if (a >= 10)
	{
		write(a / 10);
	}
	putchar(a % 10 + '0');
}