#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define ll long long
const ll INF = 1e7;
const int N = 1e5+5;
const ll P = 1e9+7;
inline int read()
{
    char c = getchar();
    ll x = 0, s = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * s;
}
struct edge{
    int v, pre;
    ll w;
}e[N<<1];
int h[N<<1], cnt;
void add(int u, int v, ll w){
    e[++cnt].v = v;
    e[cnt].w = w;
    e[cnt].pre = h[u];
    h[u] = cnt;
}
ll s[N]; int dep[N], f[N][22];
void dfs(int u, int fa, int d){
    dep[u]=d;
    for(int i=h[u];i;i=e[i].pre){
        if(e[i].v==fa) continue;
        s[e[i].v]=s[u]+e[i].w;
        f[e[i].v][0]=u;
        dfs(e[i].v,u,d+1);
    }
}
int lca(int x, int y){
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=20;i>=0;i--)
        if(dep[f[x][i]]>=dep[y])
            x=f[x][i];
    if(x==y) return x;
    for(int i=20;i>=0;i--)
        if(f[x][i]!=f[y][i]){
            x=f[x][i], y=f[y][i];
        }
    return f[x][0];
}
int main()
{
    int n,x,y,m;
    ll w;
    n=read();
    for(int i=1;i<n;i++){
        x=read(); y=read();
        w=read();
        add(x,y,w); add(y,x,w);
    }
    dfs(1,0,1);
    for(int j=1;j<=20;j++)
        for(int i=1;i<=n;i++)
            f[i][j]=f[f[i][j-1]][j-1];
    m=read();
    while(m--){
        x=read(); y=read();
        // cout<<lca(x,y)<<" ";
        cout<<s[x]+s[y]-(s[lca(x,y)]*2)<<endl;
    }
    return 0;
}