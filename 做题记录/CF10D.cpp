#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 505;

int dp[maxn];
int from[maxn];
int a[maxn];
int b[maxn];
int ans[maxn];

int main()
{
	int n, m;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	scanf("%d", &m);
	for (int i = 1; i <= m; ++i)
		scanf("%d", &b[i]);
	for (int i = 1; i <= n; ++i)
	{
		int now = 0;
		for (int j = 1; j <= m; ++j)
		{
			if (a[i] == b[j] && dp[j] < dp[now] + 1)
			{
				dp[j] = dp[now] + 1;
				from[j] = now;
			}
			if (a[i] > b[j] && dp[j] > dp[now])
				now = j;
		}
	}
	int FF = 0;
	for (int i = 1; i <= m; ++i)
		if (dp[FF] < dp[i])
			FF = i;
	printf("%d\n", dp[FF]);
	int top = 0;
	for (int i = FF; i; i = from[i])
		ans[++top] = b[i];
	for (; top; top--)
		printf("%d ", ans[top]);
	return 0;
}
