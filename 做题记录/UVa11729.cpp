#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 1005;

struct sxd
{
	int a, b;

	friend bool operator < (sxd a, sxd b)
	{
		return a.b > b.b;
	}
} a[maxn];

int main()
{
	int kase = 0, n;
	while(scanf("%d", &n) == 1 && n)
	{
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			scanf("%d%d", &a[i].a, &a[i].b);
		sort(a + 1, a + n + 1);
		for(int i = 1, now = 0; i <= n; ++i)
		{
			now += a[i].a;
			ans = max(now + a[i].b, ans);
		}
		printf("Case %d: %d\n", ++kase, ans);
	}
	return 0;
}