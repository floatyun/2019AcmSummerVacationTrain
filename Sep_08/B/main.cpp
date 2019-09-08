// lsq 
// https://nanti.jisuanke.com/t/41349
#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#define LL long long
#define MAXN 1010
#define INF 2000000000
using namespace std;
LL d[MAXN];
LL f[MAXN];
int ST,K;
LL C;
int n, m;
const int MaxN = 1010, MaxM = 1010010;
struct route {
	struct edge {
		int to, dis, next;
	};

	edge e[MaxM];
	int head[MaxN], cnt;
	bool vis[MaxN];

	void clear(){
		cnt = 0;
		for(int i = 1;i <= n + 10;i ++)
			head[i] = 0;
	}

	void add_edge( int u, int v, int d ) {
		cnt++;
		e[cnt].dis = d;
		e[cnt].to = v;
		e[cnt].next = head[u];
		head[u] = cnt;
	}

	struct node {
		LL dis;
		int pos;
		bool operator <( const node &x )const {
			return x.dis < dis;
		}
	};
	
	std::priority_queue<node> q;
	
	void dijkstra(int s,LL* dis) {
		while(!q.empty())
			q.pop();
		memset(vis,0,sizeof(vis));
		dis[s] = 0;
		q.push( ( node ) {
			0, s
		} );
		while( !q.empty() ) {
			node tmp = q.top();
			q.pop();
			int x = tmp.pos, d = tmp.dis;
			if( vis[x] )
				continue;
			vis[x] = 1;
			for( int i = head[x]; i; i = e[i].next ) {
				int y = e[i].to;
				if( dis[y] > dis[x] + e[i].dis ) {
					dis[y] = dis[x] + e[i].dis;
					if( !vis[y] ) {
						q.push( ( node ) {
							dis[y], y
						} );
					}
				}
			}
		}
	}
}dij;

int main()
{
	//freopen("1.txt","r",stdin);
	int T;
	cin >> T;
	while(T --){
		cin >> n >> m >> ST >> K >> C;
		dij.clear();
		memset(f,1,sizeof(f));
		memset(d,1,sizeof(d));
		for(int i = 1;i <= K;i ++){
			int x;
			scanf("%d",&x);
			dij.add_edge(n+1,x,0);
		}
		
		for(int i = 1;i <= m;i ++){
			int x,y;
			LL l;
			scanf("%d%d%lld",&x,&y,&l);
			dij.add_edge(x,y,l);
			dij.add_edge(y,x,l);
		}
		
		dij.dijkstra(n + 1,d);
		dij.dijkstra(ST, f);
		LL maxF = -INF;
		LL maxD = -INF;
		for(int i = 1;i <= n;i ++){
			maxF = max(maxF,f[i]);
			maxD = max(maxD,d[i]);
			//cout << f[i] << endl;
			//cout << d[i] << endl;
		}
		if(maxF <= maxD * C)
			cout << maxF << endl;
		else cout << maxD << endl; 
	}
}