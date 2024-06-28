#include <iostream>
#include <algorithm>
using namespace std;
#define ll long long
const int N=2e5+5;

struct zxtr{
    int ls, rs, sum, tag;
}t[N<<6];
int pre[N], pos[N], rt[N], tot;
int build(int l, int r){
    int p=++tot;
    if(l==r) return p;
    int mid=(l+r)>>1;
    t[p].ls=build(l, mid);
    t[p].rs=build(mid+1, r);
    return p;
}
int update(int pp, int nl, int nr, int l, int r){
    int p=++tot;
    t[p]=t[pp];
    if(nl<=l&&nr>=r){
        t[p].tag++;
        return p;
    }
    int mid=(l+r)>>1;
    if(nl<=mid) t[p].ls=update(t[pp].ls, nl, nr, l, mid);
    if(mid<nr) t[p].rs=update(t[pp].rs, nl, nr, mid+1, r);
    return p;
}
int query(int p, int x, int l, int r){
    if(l==r) return t[p].tag;
    int mid=(l+r)>>1;
    if(x<=mid) return query(t[p].ls, x, l, mid)+t[p].tag;
    else return query(t[p].rs, x, mid+1, r)+t[p].tag;
}
int main()
{
    int n, q, a;
    cin>>n>>q;
    pre[0]=-1;
    for(int i=1;i<=n;i++){
        cin>>a;
        pre[i]=pos[a];
        pos[a]=i;
    }
    rt[0]=build(1,n);
    for(int i=1;i<=n;i++){
        rt[i]=rt[i-1];
        if(pre[i]&&pre[pre[i]])
            rt[i]=update(rt[i-1], pre[pre[pre[i]]]+1, pre[pre[i]], 1, n);
    }
    int ans=0, x, y, ql, qr;
    while(q--){
        cin>>x>>y;
        ql=(x+ans-1)%n+1, qr=(y+ans-1)%n+1;
        // ql=x, qr=y;
        if(ql>qr) swap(ql, qr);
        ans=query(rt[qr], ql, 1, n);
        cout<<ans<<endl;
    }
    return 0;
}