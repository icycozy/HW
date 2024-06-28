#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define ll long long
const ll INF = 1e7;
const int N = 1e5+5;
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
int n,k,a[N],L=1,R=0;
ll dp[N][22],ans,cnt[N];
ll w(int l, int r){
    while(L>l) L--, ans+=cnt[a[L]], cnt[a[L]]++;
    while(R<r) R++, ans+=cnt[a[R]], cnt[a[R]]++; 
    while(L<l) cnt[a[L]]--, ans-=cnt[a[L]], L++;
    while(R>r) cnt[a[R]]--, ans-=cnt[a[R]], R--;
    return ans;
}
void solve(int l, int r, int lp, int rp, int k){
    if(l>r) return;
    int mid=(l+r)>>1, p=0;
    for(int i=lp;i<=min(rp,mid-1);i++){
        ll res=dp[i][k-1]+w(i+1,mid);
        if(res<dp[mid][k]) p=i, dp[mid][k]=res;
    }
    solve(l, mid-1, lp, p, k);
    solve(mid+1, r, p, rp, k);
}
int main()
{
    n=read();k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    memset(dp, 0x3f, sizeof(dp));
    for(int i=1;i<=n;i++) dp[i][1]=w(1,i);
    for(int j=2;j<=k;j++)
        solve(1, n, 0, n-1, j);
    cout<<dp[n][k]<<endl;
    return 0;
}