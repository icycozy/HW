#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;
#define ll long long

const ll INF = 1e7;
const int N = 1e4+5;
const ll P = 1e9+7;
inline int read()
{
    char c = getchar();
    ll x = 0, s = 1;
    while (c < '0' || c > '9') {if (c == '-') s = -1; c = getchar();}
    while (c >= '0' && c <= '9') {x = x * 10 + c - '0'; c = getchar();}
    return x * s;
}
typedef pair<ll, ll> PLL;
priority_queue<PLL, vector<PLL>, greater<PLL>> q;
int main()
{
    int n=read();
	ll x;
	for(int i=1;i<=n;i++){
		x = read();
		q.push(make_pair(x,0));
	}
	for(int i=1;i<n;i++){
		auto u = q.top(); q.pop();
		auto v = q.top(); q.pop();
		ll sum = u.first + v.first;
		ll w = u.second + v.second + sum;
		q.push(make_pair(sum, w));
	}
	cout<<q.top().second<<endl;
    return 0;
}