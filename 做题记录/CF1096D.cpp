#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100005;

typedef long long LL;

struct ZT
{
	LL a[4];
	ZT() { memset(a, 0x3f, sizeof(a)); }
	inline LL& operator [] (int x) { return a[x]; }
};

struct DP
{
	LL a[4][4];
	inline LL* operator [] (int x) { return a[x]; }
	/**
	 * 0 : É¶¶¼Ã»
	 * 1 : h
	 * 2 : ha
	 * 3 : har
	 **/

	DP (char c, int x)
	{
		memset(a, 0x3f, sizeof(a));
		a[0][0] = a[1][1] = a[2][2] = a[3][3] = 0;
		switch(c)
		{
			case 'h':
				a[0][1] = 0;
				a[0][0] = x;
				break;
			case 'a':
				a[1][2] = 0;
				a[1][1] = x;
				break;
			case 'r':
				a[2][3] = 0;
				a[2][2] = x;
				break;
			case 'd':
				a[3][3] = x;
		}
	}
};

inline ZT get(ZT a, DP x)
{
	ZT ans;
	for(int i = 0; i < 4; ++i)
		for(int j = 0; j <= i; ++j)
			ans[i] = min(a[j] + x[j][i], ans[i]);
	return ans;
}

char s[maxn];

int main()
{
	int n;
	scanf("%d", &n);
	scanf("%s", s + 1);
	ZT now;
	now[0] = 0;
	for(int i = 1, x; i <= n; ++i)
	{
		scanf("%d", &x);
		now = get(now, DP(s[i], x));
	}
	printf("%lld\n", min(min(now[0], now[1]), min(now[2], now[3])));
	return 0;
}
