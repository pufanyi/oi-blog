#include <cstdio>
#include <queue>

using namespace std;

typedef long long LL;

const int maxn = 5005;

priority_queue<int> q;

int main()
{
	int n;
	scanf("%d", &n);
	LL ans = 0;
	for (int i = 1, now; i <= n; ++i)
	{
		scanf("%d", &now);
		if (!q.empty() && q.top() > now)
		{
			ans += q.top() - now;
			q.pop();
			q.push(now);
			q.push(now);
		}
		else
			q.push(now);
	}
	printf("%lld", ans);
	return 0;
}
