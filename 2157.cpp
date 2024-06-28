#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#include <vector>
using namespace std;
#define ll long long
const ll INF = 1e7;
const int N = 1e5+5;
const ll P = 1e9+7;
inline int read()
{
    char c = getchar();
    ll x = 0, s = 1;
    while (c < '0' || c > '9') {if (c == '-') s = -1; c = getchar();}
    while (c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
    return x * s;
}
int n, m, p[105], s[105];
ll f[105][105][105], C[105][105], jc[105];

int main()
{
    int x;
    n=read();
    for(int i=1;i<=n;i++){
        x=read();
        p[x]++;
        m=max(m,x);
    }

    for(int i=0;i<=n;i++){
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%P;
    }
    jc[0]=1;
    for(int i=1;i<=n;i++) jc[i]=(jc[i-1]*i)%P;

    s[0]=p[0];
    for(int i=1;i<=m;i++) s[i]=s[i-1]+p[i];
    if(p[0]>1){
        cout<<0<<endl;
        return 0;
    }
    if(p[0]) f[0][1][1]=1;
    else f[0][1][1]=n;
    for(int i=1;i<=m;i++){
        x=s[i-1];
        for(int j=x;j<=n;j++){
            for(int k=1;k<=j;k++){
                for(int t=0;j+t<=n;t++){
                    f[i][j+t][t]=(f[i][j+t][t]+C[j+t-x][j-x]*f[i-1][j][k]%P*jc[t]%P*C[t+k-1][k-1]%P);
                }
            }
        }
    } 
    ll ans=0;
    for(int i=1;i<=m;i++)
        for(int k=1;k<=m;k++)
            ans=(ans+f[i][n][k])%P;
    cout<<ans<<endl;
    return 0;
}