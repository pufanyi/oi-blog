#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 1000005;

LL cc[maxn];
LL x[maxn];

inline void solve(int n)
{
	for(int i = 1; i <= n; ++i)
	{
		scanf("%lld", &x[i]);
		x[i] += x[i - 1];
	}
	LL m = x[n] / n;
	LL now = 0;
	for(int i = 1; i <= n; ++i, now += m)
		cc[i] = x[i - 1] - now;
	sort(cc + 1, cc + n + 1);
	int l = 1, r = n;
	LL ans = 0;
	while(l < r)
	{
		ans += cc[r] - cc[l];
		l++, r--;
	}
	printf("%lld\n", ans);
}

int main()
{
	int n;
	while(scanf("%d", &n) == 1 && n)
		solve(n);
}