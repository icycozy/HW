#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define ll long long
const ll INF = 1e7;
const int N = 50005;
const double eps=1e-7;
inline ll read()
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
ll t[N], dp[N], c, q[N];
inline ll x(ll p) {return t[p];}
inline ll y(ll p) {return dp[p]+(t[p]+c)*(t[p]+c);}
inline long double k(ll a, ll b) {
    return (long double)(y(b)-y(a))/(x(b)-x(a));
}

int main()
{
    ll n, l=1, r=0;
    n=read(); c=read();
    c++;
    for(int i=1;i<=n;i++) t[i]=read()+t[i-1]+1;
    q[++r]=0;
    for(int i=1;i<=n;i++){
        while(l<r && k(q[l], q[l+1])<=(long double)2*t[i]) l++;
        dp[i]=dp[q[l]]+(t[i]-t[q[l]]-c)*(t[i]-t[q[l]]-c);
        while(l<r && k(q[r-1], q[r])>=k(q[r], i)) r--;
        q[++r]=i;
    }
    cout<<dp[n]<<endl;
    return 0;
}