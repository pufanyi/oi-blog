#include <cstdio>
#include <bitset>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 20;
const int inf = 233333333;

int jz[maxn];
int now[maxn];
int n;

inline void read()
{
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
	{
		jz[i] = 0;
		for(int j = 1, t; j <= n; ++j)
		{
			scanf("%d", &t);
			jz[i] |= t << j;
		}
	}
}

inline int count(int x)
{
	int ans = 0;
	while(x)
	{
		x &= x - 1;
		ans++;
	}
	return ans;
}

inline int getans(int zt)
{
	int ans = count(zt);
	now[1] = jz[1] | zt;
	for(int i = 2; i <= n; ++i)
	{
		now[i] = (now[i - 1] ^ (now[i - 1] << 2)) >> 1;
		now[i] ^= now[i - 2];
		now[i] &= ((1 << (n + 1)) - 1) ^ 1;
		if((now[i] | jz[i]) != now[i])
			return inf;
		ans += count(now[i] ^ jz[i]);
	}
	return ans;
}

inline int solve()
{
	int ans = inf;
	for(int zt = 0; zt < (1 << n); ++zt)
		ans = min(getans(zt << 1), ans);
	return ans < inf ? ans : -1;
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; ++i)
	{
		read();
		printf("Case %d: %d\n", i, solve());
	}
	return 0;
}