#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n, prime[maxn >> 1], p[maxn], cnt;

inline void oula(int n)
{
	cnt = 0;
	for(int i = 2; i <= n; ++i)
	{
		if(!p[i])
			prime[++cnt] = i;
		for(int j = 1; j <= cnt && prime[j] * i <= n; ++j)
		{
			p[prime[j] * i] = 1;
			if(!(i % prime[j]))
				break;
		}
	}
}

int aa[maxn], cntt, hv[maxn];
int ans[maxn][2], anss;

int main()
{
	scanf("%d", &n);
	oula(n >> 1);
	for(int i = cnt; i; --i)
	{
		cntt = 0;
		for(int j = prime[i]; j <= n; j += prime[i])
			if(!hv[j])
				aa[++cntt] = j;
		if(cntt & 1)
		{
			swap(aa[cntt], aa[2]);
			cntt--;
		}
		for(int j = 1; j <= cntt; j += 2)
		{
			hv[aa[j]] = hv[aa[j + 1]] = 1;
			ans[++anss][0] = aa[j];
			ans[anss][1] = aa[j + 1];
		}
	}
	printf("%d\n", anss);
	for(int i = 1; i <= anss; ++i)
		printf("%d %d\n", ans[i][0], ans[i][1]);
	return 0;
}
