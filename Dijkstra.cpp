#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
#define ll long long
const int INF =0x7fffffff;
const int N = 1e6+5;
const int M = 1e6+5;
const ll P = 1e9+7;
typedef pair<int, int> PIL;
inline int read()
{
    char c = getchar();
    ll x = 0, s = 1;
    while (c < '0' || c > '9') {if (c == '-') s = -1; c = getchar();}
    while (c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
    return x * s;
}
struct edge {
	int to, pre;
	int w;
}e[M<<1];
int h[N], cnt;
void add(int u, int v, int w) {
	e[++cnt].to = v;
	e[cnt].w = w;
	e[cnt].pre = h[u];
	h[u] = cnt;
}

priority_queue<PIL, vector<PIL>, greater<PIL>> q;
int d[N];
bool vis[N];
int main()
{
    int n,m,s,t;
	n=read(); m=read(); s=read(); t=read();
	int u,v; ll w;
	for(int i=1;i<=m;i++){
		u=read(); v=read(); w=read();
		add(u,v,w); add(v,u,w);
	}
	for(int i=1;i<=n;i++) d[i] = INF;
	d[s] = 0;
	q.push({0,s});
	while(!q.empty()) {
		int u = q.top().second; q.pop();
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i=h[u];i;i=e[i].pre){
			int v = e[i].to;
			if(d[u]+e[i].w<d[v]){
				d[v] = d[u]+e[i].w;
				q.push({d[v],v});
			}
		}
	}
	cout<<d[t]<<endl;
    return 0;
}