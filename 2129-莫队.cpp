#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define ll long long
const ll INF = 1e7;
const int N = 50005;
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

struct Node{
    int l, r, id;
}q[N];
int n, m, k, a[N], block;
ll ans[N], b[N], b2[N], res;
inline bool cmp(Node x, Node y){
    if((x.l-1)/block != (y.l-1)/block) return x.l<y.l;
    int bl = (x.l-1)/block+1;
    return (bl&1) ? x.r<y.r : x.r>y.r;
}
inline void add(int x){
    res+=3*b2[x]+3*b[x]+1;
    b2[x]+=2*b[x]+1;
    b[x]++;
}
inline void del(int x){
    res=res-3*b2[x]+3*b[x]-1;
    b2[x]-=2*b[x]-1;
    b[x]--;
}
int main()
{
    n=read(); m=read(); k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=m;i++) q[i].l=read(), q[i].r=read(), q[i].id=i;
    block = sqrt(n);
    sort(q+1, q+m+1, cmp);
    int L=1, R=0; res=0;
    for(int i=1;i<=m;i++){
        while(L>q[i].l) L--, add(a[L]);
        while(R<q[i].r) R++, add(a[R]);
        while(L<q[i].l) del(a[L]), L++;
        while(R>q[i].r) del(a[R]), R--;
        ans[q[i].id] = res;
    }
    for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
    return 0;
}