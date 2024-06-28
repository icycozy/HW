#include <iostream>
#include <map>
using namespace std;
#define ll long long
int main()
{
    multimap<pair<ll, ll>, int> stu; // 鸣谢chengyongsen同学点醒
    int n, k;
    ll h, w, ans = 0;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> h >> w;
        stu.insert({{h, w}, i});
    }
    cin >> k;
    for (int sumh = 0; sumh <= k; sumh++)
    {
        for (auto it = stu.begin(); it != stu.end(); it++)
        {
            ll findh = sumh ^ (it->first.first), findw = (k - sumh) ^ (it->first.second);
            ans += stu.count({findh, findw});
        }
    }
    if (!k)
        cout << (ans - n) / 2;
    else
        cout << ans / 2;
    return 0;
}