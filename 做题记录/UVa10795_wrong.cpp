#include <cstdio>

typedef long long LL;

int f[70], t[70];

inline LL zhuan(int* a, int k, int to)
{
	if(!k)
		return 0;
	if(a[k] == to)
		return zhuan(a, k - 1, to);
	else
		return zhuan(a, k - 1, 6 - to - a[k]) + (1LL << (k - 1));
}

int main()
{
	// freopen("in.txt", "r", stdin);
	// freopen("out.txt", "w", stdout);
	int kase = 0, n;
	while(scanf("%d", &n) == 1 && n)
	{
		for(int i = 1; i <= n; ++i)
			scanf("%d", &f[i]);
		for(int i = 1; i <= n; ++i)
			scanf("%d", &t[i]);
		while(n && f[n] == t[n])
			n--;
		LL ans = 0;
		if(n)
			ans = zhuan(f, n - 1, 6 - f[n] - t[n])
			      + zhuan(t, n - 1, 6 - f[n] - t[n]) + 1;
		printf("Case %d: %lld\n", ++kase, ans);
	}
	// fclose(stdin);
	// fclose(stdout);
	return 0;
}