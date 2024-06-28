#include<iostream>
using namespace std;
typedef long long ll;
#define ls t[x].son[0]
#define rs t[x].son[1]
const int N=1e5+50;
inline int read(){
	int x=0;bool f=1;char c;
	while((c=getchar())<'0'||c>'9') if(c=='-') f=0;
	while(c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?x:-x;
}
struct node {
	int son[2], val, dis, rt;
}t[N];

int getf(int x) {
	return t[x].rt == x ? x : t[x].rt = getf(t[x].rt);
}
int merge(int x, int y) {
	if(!x || !y) return x + y;
	// if(t[x].val > t[y].val || (t[x].val==t[y].val && x>y)) swap(x, y);
	if(t[x].val > t[y].val) swap(x, y); // ?
	rs = merge(rs, y);
	if(t[ls].dis < t[rs].dis) swap(ls, rs);
	t[x].dis = t[rs].dis + 1;
	return x;
}
void pop(int x) {
	t[x].val = -1;
	t[ls].rt = t[rs].rt = t[x].rt = merge(ls, rs);
}

int main()
{
	int n,m,op,x,y;
	n=read(); m=read();
	for(int i=1;i<=n;i++) {
		t[i].rt = i;
		t[i].val = read();
	}
	t[0].dis = -1;
	while(m--) {
		op = read();
		if(op == 1) {
			x=read(); y=read();
			if(t[x].val==-1 || t[y].val == -1) continue;
			x = getf(x), y = getf(y);
			if(x!=y) t[x].rt = t[y].rt = merge(x, y);
		}
		else {
			x=read();
			if(t[x].val == -1) cout<<-1<<endl;
			else {
				x = getf(x);
				cout<<t[x].val<<endl;
				pop(x);
			}
		}
	}
	return 0;
}