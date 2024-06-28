#include <iostream>
using namespace std;

#define ll long long
const ll p=2019;

int main()
{
    ll a,n,ans=1;
    cin>>a>>n;
    while(n){
        if(n&1) ans=ans*a%p;
        a=a*a%p;
        n>>=1;
    }
    cout<<ans<<endl;
    return 0;
}