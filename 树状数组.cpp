int lowbit(int x) {return x & -x;}

void add(int x, int c)
{
    for (int i = x; i <= n; i += lowbit(i)) tr[i] += c;
}

int sum(int x)
{
    int res = 0;
    for (int i = x; i; i -= lowbit(i)) res += tr[i];
    return res;
}

// 段更新+点查询：令b[i]=a[i]-a[i-1]
// 段更新+段查询：令c[i]=(i-1)*b[i]
//                  c[i]+=(i-1)*x, c[j+1]-=j*x
//                  S(i)=i*sigma(b[k])-sigma(c[k])