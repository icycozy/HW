#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
#define ll long long
const ll INF = 1e7;
const int N = 1e5 + 5;
inline int read()
{
    char c = getchar();
    ll x = 0, s = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * s;
}

int n, pri[N], cnt;
bool judge[N];
void get_prime()
{
    judge[0] = judge[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (!judge[i])
            pri[++cnt] = i;
        for (int j = 1; j <= cnt && pri[j] * i <= n; j++)
        {
            judge[pri[i] * i] = 1;
            if (!(i % pri[j]))
                break;
        }
    }
}
void Exgcd(int a, int b, int &x, int &y)
{
    if (!b)
        x = 1, y = 0;
    else
        Exgcd(b, a % b, y, x), y -= a / b * x;
}
int pow(int a, int x, int p)
{
    int ans = 1;
    while (x)
    {
        if (x & 1)
            ans = ans * a % p;
        a = a * a % p;
        x >>= 1;
    }
    return ans;
}
int main()
{
    int y, e, p, q, d, x;
    bool flag;
    y = read();
    n = read();
    e = read();
    cin >> flag;
    get_prime();
    for (int i = 2; i * i <= n; i++)
    {
        if (judge[i])
            continue;
        if (!(n % i))
        {
            p = i;
            q = n / i;
            break;
        }
    }
    Exgcd(e, (p - 1) * (q - 1), d, x);
    d = (d + (p - 1) * (q - 1)) % ((p - 1) * (q - 1));
    x = pow(y, d, n);
    if (flag)
        cout << x << " " << d << endl;
    else
        cout << x << endl;
    return 0;
}