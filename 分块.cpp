#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll Maxn=1e5+7;
ll L[Maxn],R[Maxn],sum[Maxn],a[Maxn],bl,q,pos[Maxn],n,mul[Maxn],add[Maxn],mod;
inline void reset(ll x){
	for(ll i=L[x];i<=R[x];i++) 
		a[i]=(a[i]*mul[x]+add[x])%mod;
	add[x]=0,mul[x]=1;
}
inline void modify1(ll l,ll r,ll k){
	ll ql=pos[l],qr=pos[r];
	reset(ql);
	if(ql==qr){
		for(ll i=l;i<=r;i++) sum[ql]+=(k-1)*a[i]%mod,a[i]=a[i]*k%mod;
		return ;
	}
	for(ll i=l;i<=R[ql];i++)sum[ql]+=(k-1)*a[i]%mod,a[i]=a[i]*k%mod;
	reset(qr);
	for(ll i=L[qr];i<=r;i++) sum[qr]+=(k-1)*a[i]%mod,a[i]=a[i]*k%mod;
	for(ll i=ql+1;i<qr;i++) mul[i]=mul[i]*k%mod,add[i]=add[i]*k%mod,sum[i]=sum[i]*k%mod;
}
inline void modify2(ll l,ll r,ll k){
	ll ql=pos[l],qr=pos[r];
	reset(ql);
	if(ql==qr){
		sum[ql]=(sum[ql]+(r-l+1)*k)%mod;
		for(ll i=l;i<=r;i++) a[i]+=k;
		return ;
	}
	sum[ql]=(sum[ql]+(R[ql]-l+1)*k)%mod;
	for(ll i=l;i<=R[ql];i++) a[i]+=k;
	reset(qr);
	sum[qr]=(sum[qr]+(r-L[qr]+1)*k)%mod;
	for(ll i=L[qr];i<=r;i++) a[i]+=k;
	for(ll i=ql+1;i<qr;i++) add[i]+=k,sum[i]=(sum[i]+(R[i]-L[i]+1)*k)%mod;
}
inline ll query(ll l,ll r){
	ll ql=pos[l],qr=pos[r],res=0;
	if(ql==qr){
		for(ll i=l;i<=r;i++) res=(res+a[i]*mul[ql]+add[ql])%mod;
		return res;
	}
	for(ll i=l;i<=R[ql];i++) res=(res+a[i]*mul[ql]+add[ql])%mod;
	for(ll i=L[qr];i<=r;i++) res=(res+a[i]*mul[qr]+add[qr])%mod;
	for(ll i=ql+1;i<qr;i++) res+=sum[i],res%=mod;
	return res%mod;
}
int main(){
	scanf("%lld%lld%lld",&n,&q,&mod);
	for(ll i=1;i<=n;i++) scanf("%lld",&a[i]);
	bl=sqrt(n);
	for(ll i=1;i<=bl;i++){
		L[i]=R[i-1]+1;
		R[i]=i*bl;
	}
	if(R[bl]<n) ++bl,L[bl]=R[bl-1]+1,R[bl]=n;
	for(ll i=1;i<=bl;i++)
		for(ll j=L[i];j<=R[i];j++)
			pos[j]=i,sum[i]+=a[j],mul[i]=1;
	while(q--){
		ll opt,l,r,k;
		scanf("%lld%lld%lld",&opt,&l,&r);
		if(opt==1) scanf("%lld",&k),modify1(l,r,k);
		if(opt==2) scanf("%lld",&k),modify2(l,r,k);
		if(opt==3) printf("%lld\n",query(l,r)); 
	}
	return 0;
}