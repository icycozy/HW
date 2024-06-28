#include <iostream>
#include <string>
#include <map>
using namespace std;

map<int, int> mp;
void PreProcess()
{
    bool vis[6] = {0};
    int sum = 0;
    for (int i = 1; i <= 5; i++)
    {
        vis[i] = 1;
        for (int j = 1; j <= 5; j++)
        {
            if (vis[j])
                continue;
            vis[j] = 1;
            for (int k = 1; k <= 5; k++)
            {
                if (vis[k])
                    continue;
                vis[k] = 1;
                for (int p = 1; p <= 5; p++)
                {
                    if (vis[p])
                        continue;
                    vis[p] = 1;
                    for (int q = 1; q <= 5; q++)
                    {
                        if (vis[q])
                            continue;
                        mp[i * 10000 + j * 1000 + k * 100 + p * 10 + q] = ++sum;
                    }
                    vis[p] = 0;
                }
                vis[k] = 0;
            }
            vis[j] = 0;
        }
        vis[i] = 0;
    }
}

long long int Cal(char ch[], int a)
{
    map<char, int> m;
    m['e'] = 1;
    m['m'] = 2;
    m['n'] = 3;
    m['o'] = 4;
    m['y'] = 5;
    int qwq = m[ch[a - 4]] * 10000 + m[ch[a - 3]] * 1000 + m[ch[a - 2]] * 100 + m[ch[a - 1]] * 10 + m[ch[a]];
    int k = mp[qwq];
    return (long long int)k * k;
}

int main()
{
    char ch[100005]; // money  e<m<n<o<y
    bool ju[100005] = {0};
    long long int ans = 0;
    int count = 0, len = 0;
    cin.getline(ch, 100005, '\n');
    PreProcess();
    for (int i = 0; ch[i] != '\0'; i++)
    {
        ++len;
        ju[i] = 1;
        if (ch[i] == 'e' || ch[i] == 'm' || ch[i] == 'n' || ch[i] == 'o' || ch[i] == 'y')
            ju[i] = 0;
    }
    for (int i = 4; i < len; i++)
    {
        if (ju[i] || ju[i - 1] || ju[i - 2] || ju[i - 3] || ju[i - 4])
            continue;
        if (ch[i] == ch[i - 1] || ch[i] == ch[i - 2] || ch[i] == ch[i - 3] || ch[i] == ch[i - 4] || ch[i - 1] == ch[i - 2] || ch[i - 1] == ch[i - 3] || ch[i - 1] == ch[i - 4] || ch[i - 2] == ch[i - 3] || ch[i - 2] == ch[i - 4] || ch[i - 3] == ch[i - 4])
            continue;
        ans += (++count) * Cal(ch, i);
    }
    cout << ans << endl;
    return 0;
}