#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 100005, maxm = 100005;

int aa[maxn];
int now[maxn];
int n, m;

inline bool pan(LL x)
{
	for (int i = 1; i <= n; ++i)
		now[i] = aa[i];
	int noww = n;
	for (int i = 1; i <= m; ++i)
	{
		LL tx = x;
		while (!now[noww] && noww)
			noww--;
		if (!noww)
			return true;
		tx -= noww;
		if (tx < 0)
			return false;
		while (tx >= 0)
		{
			if (now[noww] > tx)
			{
				now[noww] -= tx;
				break;
			}
			else
			{
				tx -= now[noww];
				now[noww] = 0;
				while (!now[noww] && noww)
					noww--;
				if (!noww)
					return true;
			}
		}
	}
	while (!now[noww] && noww)
		noww--;
	return !noww;
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &aa[i]);
	LL l = 0, r = 0x3f3f3f3f3f3f3f3f;
	while (l < r)
	{
		LL mid = (l + r) >> 1;
		if (pan(mid))
			r = mid;
		else
			l = mid + 1;
	}
	printf("%I64d\n", l);
	return 0;
}
