#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
#define ll long long
const int INF =0x7fffffff;
const int N = 1e5+5;
const int M = 1e5+5;
const ll P = 1e9+7;
typedef pair<int, int> PII;
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
}e[M<<1];
int h[N], cnt;
void add(int u, int v) {
	e[++cnt].to = v;
	e[cnt].pre = h[u];
	h[u] = cnt;
}
int dfn[N], low[N], tim;
int s[N], top, scc[N], sum;
bool ins[N];
void dfs(int u) {
	dfn[u] = low[u] = ++tim;
	s[++top] = u;
	ins[u] = 1;
	for(int i=h[u];i;i=e[i].pre) {
		int v = e[i].to;
		if(!dfn[v]) {
			dfs(v);
			low[u] = min(low[u], low[v]);
		}
		else if(ins[v])
			low[u] = min(low[u], dfn[v]);
	}
	if(dfn[u] == low[u]) {
		++sum;
		while(s[top+1]!=u) {
			scc[sum]++;
			ins[s[top]] = 0;
			--top;
		}
	}
}
int main()
{
    int n,m,u,v;
	n=read(); m=read();
	for(int i=1;i<=m;i++) {
		u=read(); v=read();
		add(u,v);
	}
	for(int i=1;i<=n;i++)
		if(!dfn[i])
			dfs(i);
	ll ans = 0;
	for(int i=1;i<=sum;i++){
		ans += (ll)scc[i]*(scc[i]-1)/2;
	}
	cout<<ans<<endl;
    return 0;
}