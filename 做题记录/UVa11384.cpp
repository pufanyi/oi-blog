#include <cstdio>

int main()
{
	int n, ans;
	while(scanf("%d", &n) == 1)
	{
		ans = 0;
		while(n)
			n >>= 1, ans++;
		printf("%d\n", ans);
	}
	return 0;
}