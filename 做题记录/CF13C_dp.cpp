#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 5005;

LL dp[maxn];
LL a[maxn];
LL b[maxn];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%lld", &a[i]);
		b[i] = a[i];
	}
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; ++i)
	{
		dp[1] += abs(a[i] - b[1]);
		for (int j = 2; j <= n; ++j)
			dp[j] = min(dp[j - 1], dp[j] + abs(a[i] - b[j]));
	}
	printf("%lld", dp[n]);
	return 0;
}
