#include <iostream>
#include <algorithm>
#include <cstring>
#define ll long long
using namespace std;

int m;
int cal(int pos, int n, bool dir)
{
   if (n == 1)
      return 1;
   int x = (m - 1) % (2 * n - 2); // 走x步
   int res, kill;

   if(pos!=1&&pos!=n&&(!dir)) pos=2*n-pos;

   kill=(pos+x-1)%(2*n-2)+1;
   if(kill>=n){
      dir=0;
      kill=2*n-kill;
      res=cal(kill-1,n-1,0);
   }
   else{
      dir=1;
      res=cal(kill,n-1,1);
   }



   // cout<<n<<" pos:"<<pos<<" dir:"<<dir<<" "<<res<<endl;
   if (res >= kill)
      return res + 1;
   else
      return res;
}
int main()
{
   int n;
   cin >> n >> m;
   cout << cal(1, n, 1) << endl;
   return 0;
}