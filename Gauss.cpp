#include <iostream>
#include <cmath>
using namespace std;
#define ll long long
const ll P = 998244353;

ll qpow(ll a, ll n) {
    ll ans=1;
    while(n){
        if(n & 1) ans = ans * a % P;
        a = a * a % P;
        n >>= 1;
    }
    return ans;
}
ll inv(ll a) {
    return qpow(a, P-2);
}

int n,zy[305];
ll a[305][305],x[305];
int gauss() {
    int r=1;
    for(int c=1;c<=n;c++){
        int i=0;
        for(int j=r;j<=n;j++)
            if(a[j][c]) {i=j;break;}
        if(!i) continue;
        zy[r]=c;
        for(int j=c;j<=n+1;j++) swap(a[i][j],a[r][j]);
        ll t = inv(a[r][c]);
        for(int j=c;j<=n+1;j++) a[r][j]=(a[r][j]*t)%P;
        for(int k=r+1;k<=n;k++){
            t=a[k][c];
            for(int j=c;j<=n+1;j++)
                a[k][j]=(a[k][j]+((P-t)*a[r][j])%P)%P;
        }
        r++;
    }
    for(int i=r;i<=n;i++) if(a[i][n+1]) return -1;
    return r-1;
}

void Cal(int c, int r) {
    if(!c) {
        for(int i=1;i<=n;i++)
            cout<<x[i]<<" ";
        cout<<endl;
        return;
    }
    if(c==zy[r]){
        x[c]=a[r][n+1];
        for(int j=n;j>c;j--) x[c]=(x[c]+((P-x[j])*a[r][j])%P)%P;
        Cal(c-1,r-1);
    }
    else{
        x[c]=0;
        Cal(c-1,r);
    }
}

int main() {   
    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n+1;j++){
            cin>>a[i][j];
            a[i][j]%=P;
        }
    int r = gauss();
    if(r==-1) return cout<<"No Solution"<<endl, 0;
    if(r<n) return cout<<"No Unique Solution"<<endl, 0;
    Cal(n,r);
    return 0;
}