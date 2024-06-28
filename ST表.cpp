#include<iostream>
using namespace std;
int n, q;
const int MAXN = 5e4+5,MAX_L = 20;
int log_2[MAXN];
int stmin[MAXN][MAX_L];
int stmax[MAXN][MAX_L];
 
int main()
{
	cin >> n >> q;
	log_2[0] = -1;
	for (int i = 1; i <= n; i++)
	{
		cin >> stmax[i][0];
		stmin[i][0] = stmax[i][0];
		log_2[i] = log_2[i >> 1] + 1;
	}
	for (int j = 1; (1 << j) <= n; j++)
	{
		for (int i = 1; i + (1 << j) - 1 <= n; i++)
		{
			stmin[i][j] = min(stmin[i][j - 1], stmin[i + (1 << j - 1)][j - 1]);
			stmax[i][j] = max(stmax[i][j - 1], stmax[i + (1 << j - 1)][j - 1]);
		}
	}
	while(q--)
	{
		int l, r;
		cin >> l >> r;
		int x = log_2[r - l + 1];
		cout << max(stmax[l][x], stmax[r - (1 << x) + 1][x]) - min(stmin[l][x], stmin[r - (1 << x) + 1][x]) << endl;
	}
}