#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
#define ll long long
const ll INF = 1e7;
const int N = 4e5+5;
const ll P = 1e9+7;
const double Pi = acos(-1.0);
inline int read()
{
    char c = getchar();
    ll x = 0, s = 1;
    while (c < '0' || c > '9') {if (c == '-') s = -1; c = getchar();}
    while (c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
    return x * s;
}
struct complex{
    double x, y;
    complex(double a=0, double b=0): x(a), y(b){};
}a[N<<1],b[N<<1];
complex operator + (complex a, complex b) {return complex(a.x+b.x, a.y+b.y);}
complex operator - (complex a, complex b) {return complex(a.x-b.x, a.y-b.y);}
complex operator * (complex a, complex b) {return complex(a.x*b.x-a.y*b.y, a.x*b.y+a.y*b.x);}

// void FFT(int limit, complex *a, int flag){
//     if(limit==1) return;
//     complex a1[limit>>1], a2[limit>>1];
//     for(int i=0;i<limit;i+=2)
//         a1[i>>1]=a[i], a2[i>>1]=a[i+1];
//     FFT(limit>>1,a1,flag);
//     FFT(limit>>1,a2,flag);
//     complex wn=complex(cos(2.0*Pi/limit), flag*sin(2.0*Pi/limit)), w=complex(1,0);
//     for(int i=0;i<(limit>>1);i++,w=w*wn){
//         complex t=w*a2[i];
//         a[i]=a1[i]+t;
//         a[i+(limit>>1)]=a1[i]-t;
//     }
// }

int R[N<<1];
void FFT(int limit, complex *a, int flag){
    for(int i=0;i<limit;i++)
        if(i<R[i]) swap(a[i],a[R[i]]);
    for(int mid=1;mid<limit;mid<<=1){
        complex wn(cos(Pi/mid), flag*sin(Pi/mid));
        for(int r=mid<<1,j=0;j<limit;j+=r){
            complex w(1,0);
            for(int k=0;k<mid;k++, w=w*wn){
                complex x=a[j+k], y=w*a[j+mid+k];
                a[j+k]=x+y;
                a[j+mid+k]=x-y;
            }
        }
    }
}
int main()
{
    int n,m;
    n=read(); m=read();
    for(int i=0;i<=n;i++) a[i].x=read();
    for(int i=0;i<=m;i++) b[i].x=read();
    int limit=1,L=0;
    while(limit<=n+m) limit<<=1, L++;
    for(int i=0;i<limit;i++)
        R[i]=(R[i>>1]>>1) | ((i&1)<<(L-1)); // reverse
    FFT(limit,a,1); FFT(limit,b,1);
    for(int i=0;i<=limit;i++) a[i]=a[i]*b[i];
    FFT(limit,a,-1);
    for(int i=0;i<=n+m;i++) cout<<(int)(a[i].x/limit+0.5)<<" "; // 四舍五入
    cout<<endl;
    return 0;
}