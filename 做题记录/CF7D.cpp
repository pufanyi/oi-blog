#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 5000005;

typedef unsigned long long HASH_int;

char aa[maxn];
int dp[maxn];

int main()
{
	gets(aa + 1);
	int n = strlen(aa + 1);
	HASH_int qian = 0, hou = 0;
	long long ans = 0;
	HASH_int now = 1;
	for (int i = 1; i <= n; ++i)
	{
		qian += (HASH_int)aa[i] * aa[i] * aa[i] * now;
		hou *= 233;
		hou += (HASH_int)aa[i] * aa[i] * aa[i];
		now *= 233;
		if (qian == hou)
		{
			dp[i] = dp[i >> 1] + 1;
			ans += dp[i];
		}
	}
	printf("%lld", ans);
	return 0;
}
