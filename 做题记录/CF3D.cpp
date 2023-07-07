#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL maxn = 500005;

char s[maxn];

typedef pair<LL, LL> pii;

int main()
{
	LL now = 0;
	scanf("%s", s);
	LL len = strlen(s);
	LL ans = 0;
	priority_queue<pii, vector<pii>, greater<pii> > q;
	while (!q.empty())
		q.pop();
	for (LL i = 0; i < len; ++i)
	{
		if (s[i] == '(')
			now++;
		else if (s[i] == ')')
			now--;
		else if (s[i] == '?')
		{
			LL L, R;
			scanf("%lld%lld", &L, &R);
			now--;
			ans += R;
			s[i] = ')';
			q.push(make_pair(L - R, i));
		}
		if (now < 0)
		{
			if (q.empty())
			{
				puts("-1");
				return 0;
			}
			else
			{
				pii Now = q.top();
				q.pop();
				s[Now.second] = '(';
				ans += Now.first;
				now += 2;
			}
		}
	}
	if (now)
	{
		puts("-1");
		return 0;
	}
	printf("%lld\n", ans);
	puts(s);
	return 0;
}
