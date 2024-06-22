#include <iostream>

typedef long long LL;

const int maxn = 36;

LL dp[maxn][maxn];

int main()
{
	LL n, h;
	std::cin >> n >> h;
	for (int i = 0; i <= n; ++i)
		dp[0][i] = 1;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= n; ++j)
		{
			LL ans = 0;
			for (int k = 0; k < i; ++k)
				ans += dp[k][j - 1] * dp[i - k - 1][j - 1];
			dp[i][j] = ans;
		}
	}
	std::cout << dp[n][n] - dp[n][h - 1];
	return 0;
}
