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
int tim, tr[N<<3];
inline int lowbit(int x) {return x&(-x);}
void add(int x, int c) {
    for (int i = x; i <= tim; i += lowbit(i)) tr[i] += c;
}
int query(int x) {
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

int h[N],to[N<<1],pre[N<<1],cnt;
void adde(int u, int v){
    to[++cnt]=v;
    pre[cnt]=h[u];
    h[u]=cnt;
}

int ch[N][26],fa[N],pos[N],tot,fail[N];
void GetFail() {
    queue<int> q;
    for(int i=0;i<26;i++)
        if(ch[0][i])
            q.push(ch[0][i]);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int i=0;i<26;i++){
            if(!ch[u][i]) ch[u][i]=ch[fail[u]][i];
            else fail[ch[u][i]]=ch[fail[u]][i], q.push(ch[u][i]);
        }
    }
}
int in[N],out[N],ans[N];
void dfs(int u){
    in[u]=++tim;
    for(int i=h[u];i;i=pre[i])
        dfs(to[i]);
    out[u]=++tim;
}

vector<pair<int,int>> v[N];
int main()
{
    string s;
    int n, m, now=0, sum=0;
    cin>>s; n=s.size();
    for(int i=0;i<n;i++){
        if(s[i]>='a'&&s[i]<='z'){
            if(!ch[now][s[i]-'a']) fa[++tot]=now, ch[now][s[i]-'a']=tot;
            now=ch[now][s[i]-'a'];
        }
        else if(s[i]=='P') pos[++sum]=now;
        else now=fa[now];
    }
    GetFail();
    for(int i=1;i<=tot;i++)
        adde(fail[i],i);
    dfs(0);

    int x,y;
    m=read();
    for(int i=1;i<=m;i++){
        x=read();y=read();
        v[y].push_back(make_pair(x,i));
    }

    now=sum=0;
    for(int i=0;i<n;i++){
        if(s[i]>='a'&&s[i]<='z'){
            now=ch[now][s[i]-'a'];
            add(in[now],1);
        }
        else if(s[i]=='B'){
            add(in[now],-1);
            now=fa[now];
        }
        else{
            sum++;
            for(int j=0;j<v[sum].size();j++)
                ans[v[sum][j].second]=query(out[pos[v[sum][j].first]])-query(in[pos[v[sum][j].first]]-1);
        }
    }
    for(int i=1;i<=m;i++)
        cout<<ans[i]<<endl;
    return 0;
}