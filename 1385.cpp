#include <iostream>
#include <cmath>
using namespace std;
const int N = 1e8;
// 参考了一个神奇的公式
// https://www.campusgate.in/2013/10/finding-right-most-non-zero-digit-of.html
long long cnt;
int Cal(int n)
{
    if (n == 0 || n == 1)
        return 1;
    if (n == 2)
        return 2;
    if (n == 3)
        return 6;
    if (n == 4)
        return 4;
    cnt += n / 5;
    return Cal(n / 5) * Cal(n % 5) % N;
}
int main()
{
    int n;
    cin >> n;
    long long ans = Cal(n);
    while (cnt--)
        ans = (ans << 1) % N;
    cout << ans % 10 << endl;
    return 0;
}