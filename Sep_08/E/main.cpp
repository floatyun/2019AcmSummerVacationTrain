// lsq https://nanti.jisuanke.com/t/41352
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
int T;
int n,m,Q;
deque<int> q;
int a[40001000];
inline int read() {
    char ch = getchar(); int x = 0, f = 1;
    while(ch < '0' || ch > '9') {
        if(ch == '-') f = -1;
        ch = getchar();
    } while('0' <= ch && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    } return x * f;
}
int main() {
	//freopen("1.txt","r",stdin);
	T = read();
	while(T --) {
		n = read(); m = read();
		q.clear();
		q.push_back(n);
		for(int i = n - 1; i >= 1; i --) {
			for(int j = m; j >= 1; j --) {
				q.push_front(q.back());
				q.pop_back();
			}
			q.push_front(i);
		}
		int cnt = 1;
		while(!q.empty()) {
			int t = q.front();
			a[cnt ++] = t;
			q.pop_front();
		}
		Q = read();
		for(int i = 1;i <= Q;i ++){
			int k;
			k = read();
			printf("%d\n",a[k]);
		}
	}
}