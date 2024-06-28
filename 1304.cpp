#include <iostream>
#include <cmath>
using namespace std;
#define ll long long
const double pi = 3.1415926535897932;

int main()
{
    int t, n;
    cin >> t;
    if (t == 400)
        n = 1000 - 1;
    else
        n = 400000 / t - 1;
    double theta = 2 * pi / n, r = 1e7-rand()%10000;
    printf("%d\n", n);
    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", (int)(r * cos(i * theta)), (int)(r * sin(i * theta)));
    }
    return 0;
}