#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const int inf = 0x3f3f3f3f;

int n, s1, s2;
int aa[maxn];

inline bool check(int x)
{
    int l = -inf, r = inf;
    for(int i = n; i; --i)
    {
        if(l <= aa[i] && aa[i] <= r)
            l = aa[i] - x, r = aa[i] + x;
        else
            l = max(l, aa[i] - x), r = min(r, aa[i] + x);
    }
    return (l <= s1 && s1 <= r) || (l <= s2 && s2 <= r);
}

int main()
{
    scanf("%d%d%d", &n, &s1, &s2);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &aa[i]);
    int l = abs(s1 - s2), r = inf;
    while(l < r)
    {
        int mid = (l + r) >> 1;
        if(check(mid))
            r = mid;
        else
            l = mid + 1;
    }
    printf("%d\n", l);
    return 0;
}