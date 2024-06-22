#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 10005;

char zt[][10] = {"L", "R", "Turning", "Fell off"};

struct Ant
{
	int x, zt, id;
	friend bool operator < (Ant a, Ant b)
	{
		return a.x < b.x;
	}
} a[maxn], b[maxn];

inline bool cmp(Ant a, Ant b)
{
	return a.id < b.id;
}

int idd[maxn];

inline void solve(int l, int t, int n)
{
	for(int i = 1; i <= n; ++i)
	{
		char c[3];
		scanf("%d%s", &a[i].x, c);
		a[i].zt = (c[0] == 'R');
		a[i].id = i;
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
		idd[i] = a[i].id;
	for(int i = 1; i <= n; ++i)
	{
		if(a[i].zt)
			a[i].x += t;
		else
			a[i].x -= t;
	}
	sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; ++i)
	{
		if(a[i].x == a[i - 1].x || a[i].x == a[i + 1].x)
			a[i].zt = 2;
		b[idd[i]] = a[i];
	}
	for(int i = 1; i <= n; ++i)
	{
		if(b[i].x < 0 || b[i].x > l)
			puts(zt[3]);
		else
			printf("%d %s\n", b[i].x, zt[b[i].zt]);
	}
	puts("");
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; ++i)
	{
		printf("Case #%d:\n", i);
		int l, t, n;
		scanf("%d%d%d", &l, &t, &n);
		solve(l, t, n);
	}
	return 0;
}