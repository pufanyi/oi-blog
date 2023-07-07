#include <cmath>
#include <cstdio>

using namespace std;

inline void solve(int n, int m)
{
	double ans = 0., pos;
	for(int i = 1; i < n; ++i)
	{
		pos = (double) i * (n + m) / n;
		ans += fabs(pos - floor(pos + .5));
	}
	printf("%.4f\n", ans * 10000. / (n + m));
}

int main()
{
	int n, m;
	while(scanf("%d%d", &n, &m) == 2)
		solve(n, m);
	return 0;
}