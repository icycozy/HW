#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e6+5;
inline int read(){
	int x=0;bool f=1;char c;
	while((c=getchar())<'0'||c>'9') if(c=='-') f=0;
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?x:-x;
}
int n,m,dfn[N],low[N],scc[N],num,tot,s[N],top;
bool ins[N];
vector<int> g[N];
inline void tarjan(int u){
	dfn[u]=low[u]=++num;
	s[++top]=u;ins[u]=1;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
		else if(ins[v]) low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		tot++;
		do{
			ins[s[top]]=0;
			scc[s[top]]=tot;
		}while(s[top--]!=u);
	}
}
int main()
{
	n=read(),m=read();int x,a,y,b;
	for(int i=1;i<=m;i++){
		x=read(),a=read();
		y=read(),b=read();
		g[x+n*(a&1)].push_back(y+n*(b^1));
		g[y+n*(b&1)].push_back(x+n*(a^1));
	}
	for(int i=1;i<=(n<<1);i++){
		if(!dfn[i]) tarjan(i);
	}
	for(int i=1;i<=n;i++){
		if(scc[i]==scc[i+n]){
			puts("No");
			return 0;
		}
	}
	puts("Yes");
	for(int i=1;i<=n;i++){
		//printf("%d %d %d\n",i,scc[i],scc[i+n]);
		printf("%d ",scc[i]<scc[i+n]);
	}
	return 0;
}