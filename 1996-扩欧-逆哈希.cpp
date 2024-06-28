#include <iostream>
using namespace std;
#define ll long long
const long long p = ((ll)1 << 32);

#define ROTL32(x, n) ((x) << n | (x) >> (32 - n))

// acknowledgement: Thanks Liu Siyu for his reminder of calculating the multiplicative inverse.

void Exgcd(ll a, ll b, ll &x, ll &y)
{
    if (!b)
        x = 1, y = 0;
    else
        Exgcd(b, a % b, y, x), y -= a / b * x;
}
ll inv(ll a)
{
    ll x, y;
    Exgcd(a, p, x, y);
    x = (x % p + p) % p;
    return x;
}

int main()
{
    unsigned int h, h1, h2, h3, a[55] = {0};
    ll x;
    int n;
    cin >> h >> n;

    h ^= h >> 16;
    x = inv((ll)0xc2b2ae35);
    h *= x;
    // cout << h << endl;
    h1 = h >> 19;
    h2 = (h1 ^ (h >> 6)) >> 7;
    h ^= h2;
    // cout << h << endl;
    h ^= h >> 16;
    // cout << h << endl;

    for (int i = n; i; i--)
    {
        h -= (unsigned int)0xe6546b64;
        h = ROTL32(h, 19);
        a[i] = 0;
    }
    a[1] = ROTL32(h, 17);

    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    return 0;
}