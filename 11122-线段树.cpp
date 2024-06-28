#include <iostream>
#include <algorithm>
using namespace std;
const int N=50005;

inline int ls(int p) {return p<<1;}
inline int rs(int p) {return p<<1|1;}

struct Tree{
    int m, lm, rm;
}t[N<<2];
int n;

inline void pushUp(int p, int l, int r) {
    int mid=(l+r)>>1;
    if(t[ls(p)].m>=mid-l+1) t[p].lm=t[ls(p)].rm+t[rs(p)].lm;
    else t[p].lm=t[ls(p)].lm;
    if(t[rs(p)].m>=r-mid) t[p].rm=t[ls(p)].rm+t[rs(p)].lm;
    else t[p].rm=t[rs(p)].rm;
    t[p].m=max(max(t[ls(p)].m,t[rs(p)].m),t[ls(p)].rm+t[rs(p)].lm);
}

void build(int p, int l, int r) {
    t[p].lm = t[p].rm = t[p].m = r-l+1;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(ls(p), l, mid);
    build(rs(p), mid + 1, r);
}

int tag[N<<2];

void f(int p,int l,int r,int tt) {
    tag[p]=tt;
    if(tt==1) t[p].lm=t[p].m=t[p].rm=0;
    else t[p].lm=t[p].m=t[p].rm=r-l+1;
}
void pushDown(int p, int l, int r) {
    int mid=(l+r)>>1;
    f(ls(p),l,mid,tag[p]);
    f(rs(p),mid+1,r,tag[p]);
    tag[p]=0;
}

void update(int nl, int nr, int l, int r, int p, bool flag) {
    if(nl<=l && r<=nr){
        if(flag) tag[p]=1, t[p].lm=t[p].m=t[p].rm=0; //有人
        else tag[p]=2, t[p].lm=t[p].m=t[p].rm=r-l+1;
        return;
    }
    int mid=(l+r)>>1;
    if(tag[p]) pushDown(p,l,r);
    if(nl<=mid) update(nl,nr,l,mid,ls(p),flag);
    if(nr>mid) update(nl,nr,mid+1,r,rs(p),flag);
    pushUp(p,l,r);
}

int query(int l, int r, int p, int d) {
    if(t[p].m<d) return 0;
    if(l==r) return l;
    int res=0, mid=(l+r)>>1;
    if(tag[p]) pushDown(p,l,r);
    if(t[ls(p)].m>=d) return query(l,mid,ls(p),d);
    if(t[ls(p)].rm+t[rs(p)].lm>=d) return mid-t[ls(p)].rm+1;
    return query(mid+1,r,rs(p),d);
}

int main()
{
    int m, op, x, y;
    cin>>n>>m;
    build(1, 1, n);
    while(m--){
        cin>>op;
        if(op==1){
            cin>>x;
            y=query(1,n,1,x);
            if(y) update(y,y+x-1,1,n,1,1);
            cout<<y<<endl;
        }
        else{
            cin>>x>>y;
            update(x,x+y-1,1,n,1,0);
        }
    }
    return 0;
}