#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cmath>
using namespace std;

#define ll long long

struct ele
{
    ll head,tail;
    string tp,name;
};
struct Stt
{
    int num;
    vector<ele> son;
};
vector<Stt> stu;

map<string, ll> dq, sz;
map<string, int> pos; // 对齐要求，大小，第几个结构体
vector<pair<string, string>> nam; // op2中定义的结构体类型和名称
ll beg[101], en[101];  // op2中结构体起始和终止位置

ll cnt; int cn, cs; // 内存  op2定义的结构体数量  op1定义的结构体类型数量
string an; bool f; // op4临时存储答案和是否有解

void Create()
{
    string s, s0, na;
    int k;
    ll sum = 0, m = 0;
    Stt st;
    cin >> s >> k;
    st.num = k;
    pos[s] = cs;
    for (int i = 0; i < k; i++) {
        cin >> s0 >> na;
        ele e;
        e.name=na,e.tp=s0;
        m = max(m, dq[s0]);
        if(sum) sum = ((sum - 1) / dq[s0] + 1) * dq[s0];
        e.head = sum;
        sum += sz[s0];
        e.tail = sum;
        st.son.push_back(e);
    }
    stu.push_back(st);
    cs++;
    dq[s] = m;
    sz[s] = ((sum - 1) / m + 1) * m;
    cout << sz[s] << " " << m << endl;
}
void New()
{
    string t, n;
    cin >> t >> n;
    nam.push_back({t, n});
    if (!cnt) cout << 0 << endl;
    else {
        cnt = ((cnt - 1) / dq[t] + 1) * dq[t];
        cout << cnt << endl;
    }
    beg[cn] = cnt;
    cnt += sz[t];
    en[cn] = cnt;
    cn++;
}
ll Cal(string fa, string s)
{
    int p = pos[fa];
    for (int i = 0; i < stu[p].num; i++)
        if (stu[p].son[i].name == s)
            return stu[p].son[i].head;
    return -1;
}
void Inquire()
{
    string in, s;
    int i = 0;
    cin >> in;
    int l = in.size();
    for (; i<l && in[i] != '.'; i++)
        s.push_back(in[i]);
    if(i==l)
        for (int j = 0; j < cn; j++)
            if (nam[j].second == s){
                cout<<beg[j]<<endl;
                return;
            }
    i++;
    ll ans;
    string fa;
    for (int j = 0; j < cn; j++) {
        if (nam[j].second == s) {
            ans = beg[j];
            fa = nam[j].first;
            break;
        }
    }
    s.clear();
    for (; i < l; i++) {
        if (in[i] == '.') {
            ans += Cal(fa, s);
            int p = pos[fa];
            for (int j = 0; j < stu[p].num; j++) {
                if (stu[p].son[j].name == s) {
                    fa = stu[p].son[j].tp;
                    break;
                }
            }
            s.clear();
            continue;
        }
        s.push_back(in[i]);
    }
    ans += Cal(fa, s);
    cout << ans << endl;
}
void Ad(string fa, ll adr)
{
    if (!f) return;
    for (int i = 0; i < stu[pos[fa]].num; i++) {
        ele e = stu[pos[fa]].son[i];
        if (adr >= e.head && adr < e.tail) {
            an = an + e.name;
            if ((e.tp != "byte") && (e.tp != "short") && (e.tp != "int") 
                                && (e.tp != "long")) {
                an.push_back('.');
                Ad(e.tp, adr - e.head);
            }
            return;
        }
    }
    f = 0;
    return;
}
void Addr()
{
    an.clear();
    f = 1;
    ll adr;
    int p;
    cin >> adr;
    for (p = 0; p < cn; p++) {
        if (adr >= beg[p] && adr < en[p]) {
            an = nam[p].second;
            break;
        }
    }
    if (p == cn) {
        cout << "ERR" << endl;
        return;
    }
    if(pos[nam[p].first]<4){
        cout<<an<<endl;
        return;
    }
    an.push_back('.');
    Ad(nam[p].first, adr - beg[p]);
    if (f) cout << an << endl;
    else cout << "ERR" << endl;
}

int main()
{
    Stt t; t.num=0;
    pos["byte"]=0;dq["byte"]=sz["byte"]=1;
    stu.push_back(t);
    pos["short"]=1;dq["short"]=sz["short"]=2;
    stu.push_back(t);
    pos["int"]=2;dq["int"]=sz["int"]=4;
    stu.push_back(t);
    pos["long"]=3;dq["long"]=sz["long"]=8;
    stu.push_back(t);
    cs=4;
    int n, op;
    cin >> n;
    while(n--) {
        cin >> op;
        switch (op) {
            case 1: Create(); break;
            case 2: New(); break;
            case 3: Inquire(); break;
            case 4: Addr(); break;
        }
    }
    return 0;
}