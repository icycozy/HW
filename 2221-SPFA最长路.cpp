#include <iostream>
#include <queue>
#include <vector>
#include <string.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> PIL;
const int N = 1e6+5;
const ll INF = 0x7fffffffffff*1LL;
inline ll read(){
	ll x=0;bool f=1;char c;
	while((c=getchar())<'0'||c>'9') if(c=='-') f=0;
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?x:-x;
}
struct edge {
	int from, to, nxt;
	ll w;
}e[N],e2[N];
int cnt, h[N];
void add(int u, int v, ll w) {
	e[++cnt].to = v;
	e[cnt].from = u;
	e[cnt].w = w;
	e[cnt].nxt = h[u];
	h[u] = cnt;
}
int n,m;
int dfn[N], low[N], tim;
int s[N], top, scc[N], sum, clr[N];
bool ins[N];
void tarjan(int u) {
	dfn[u] = low[u] = ++tim;
	s[++top] = u;
	ins[u] = 1;
	for(int i=h[u];i;i=e[i].nxt) {
		int v = e[i].to;
		if(!dfn[v]) {
			tarjan(v);
			low[u] = min(low[u], low[v]);
		}
		else if(ins[v])
			low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		++sum;
		while(s[top+1]!=u) {
			clr[s[top]] = sum;
			ins[s[top]] = 0;
			--top;
		}
	}
}
ll f[N];
int cnt2, h2[N], ru[N];
void add2(int u, int v, ll w) {
	e2[++cnt2].to = v;
	e2[cnt2].from = u;
	e2[cnt2].w = w;
	e2[cnt2].nxt = h2[u];
	h2[u] = cnt2;
	ru[v]++;
}
queue<PIL> q;
ll dis[N];
bool vis[N];
int main()
{
	int x,y;
	ll z;
	n=read(); m=read();
	for(int i=1;i<=m;i++) {
		x=read(); y=read(); z=read();
		add(y,x,z);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			tarjan(i);

	for(int i=1;i<=cnt;i++) {
		if(clr[e[i].from] == clr[e[i].to])
			f[clr[e[i].from]]+=e[i].w;
		else add2(clr[e[i].from], clr[e[i].to], e[i].w);
	}

	for(int i=1;i<=sum;i++) {
		dis[i] = f[i];
		if(!ru[i])
			q.push({dis[i],i});
	}

	while(!q.empty()) {
		int u = q.front().second;q.pop();
		vis[u] = 0;
		for(int i=h2[u];i;i=e2[i].nxt){
			int v = e2[i].to;
			if(dis[u]+e2[i].w+f[v]>dis[v]){
				dis[v] = dis[u]+e2[i].w+f[v];
				if(!vis[v]) q.push({dis[v],v}), vis[v]=1;
			}
		}
	}
	ll ans = 0;
	for(int i=1;i<=sum;i++) ans=max(ans,dis[i]);
	cout<<ans<<endl;
	return 0;
}