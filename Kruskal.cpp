#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;
struct edge{
    int u,v,w;
    bool operator < (const edge& edg){
        return this->w < edg.w;
    }
}e[200005];
int fa[5005];
int find(int p){
    if(fa[p]!=p) fa[p]=find(fa[p]);
    return fa[p];
}
int main()
{
    int n,m,a,b,c;
    ll ans=0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++){
        cin>>a>>b>>c;
        e[i]={a,b,c};
    }
    sort(e+1,e+m+1);
    for(int i=1;i<=m;i++){
        int fu=find(e[i].u),fv=find(e[i].v);
        if(fu!=fv){
            ans+=(ll)e[i].w;
            fa[fu]=fv;
        }
    }
    cout<<ans<<endl;
    return 0;
}