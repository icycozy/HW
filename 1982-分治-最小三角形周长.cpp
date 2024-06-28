#include <bits/stdc++.h>
using namespace std;
#define ll long long

const double INF = 1e18;

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

double pow_2(ll x)
{
    return x * x * 1.0;
}
struct point
{
    int x, y;
    double distance(const point &other) const
    {
        return sqrt(pow_2((ll)x - other.x) + pow_2((ll)y - other.y));
    }
}a[400005], tmp[400005];

double solve(int l, int r)
{
    if (l + 1 >= r)
        return INF;
    if (l + 2 == r)
    {
        if (a[l].y > a[l + 1].y)
            swap(a[l], a[l + 1]);
        return INF;
    }
    if (l + 3 == r)
    {
        sort(a + l, a + l + 3, [](auto &u, auto &v)
             { return u.y < v.y; });
        return a[l].distance(a[l + 1]) + a[l].distance(a[l + 2]) + a[l + 1].distance(a[l + 2]);
    }

    int mid = (l + r) >> 1;
    int midx = a[mid].x;
    double d = min(solve(l, mid), solve(mid, r));

    int left = l, right = mid, t = l;
    while (left < mid && right < r)
        if (a[left].y <= a[right].y)
            tmp[t++] = a[left++];
        else
            tmp[t++] = a[right++];
    while (left < mid)
        tmp[t++] = a[left++];
    while (right < r)
        tmp[t++] = a[right++];
    for (int i = l; i < r; i++)
        a[i] = tmp[i];

    int k = 0;
    for (int i = l; i < r; i++)
        if (abs(a[i].x - midx) <= d * 0.5)
            tmp[k++] = a[i];
    for (int i = 0; i < k; i++)
    {
        for (int j = i + 2; j < k; j++)
        {
            if (tmp[j].y - tmp[i].y > d * 0.5)
                break;
            for (int u = i + 1; u < j; u++)
                d = min(d, tmp[i].distance(tmp[j]) + tmp[i].distance(tmp[u]) + tmp[j].distance(tmp[u]));
        }
    }
    return d;
}

int main()
{
    int n;
    n = read();
    for (int i = 0; i < n; i++)
    {
        int x, y;
        x = read(), y = read();
        a[i] = point({x, y});
    }
    sort(a, a + n, [](auto &u, auto &v)
         { return u.x < v.x; });
    printf("%.8f",solve(0,n));
    return 0;
}