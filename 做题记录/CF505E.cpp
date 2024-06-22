#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

#define small_heap(a) a, vector<a>, greater<a>

namespace sxdaknoip
{
	const int maxn = 100005;

	typedef long long LL;
	typedef pair<LL, LL> pii;

	LL n, m, k;
	LL p;
	LL h[maxn], a[maxn], htp[maxn];
	priority_queue<small_heap(pii)> q; // <days, id>

	inline bool check(LL maxl)
	{
		while(!q.empty())
			q.pop();
		for(LL i = 1; i <= n; ++i)
		{
			htp[i] = maxl;
			if(maxl < m * a[i])
				q.push(make_pair(maxl / a[i] - 1, i));
		}
		LL tim;
		for(tim = 0; !q.empty() && tim < m * k; ++tim)
		{
			pii top = q.top();
			q.pop();
			if(top.first < tim / k)
				return false;
			LL now = top.second;
			htp[now] += p;
			if(htp[now] < m * a[now])
				q.push(make_pair(htp[now] / a[now] - 1, now));
		}
		for(LL i = 1; i <= n; ++i)
		{
			LL Tmp = h[i] - htp[i] + a[i] * m;
			if(Tmp > 0)
			{
				tim += Tmp / p;
				if(Tmp % p)
					tim++;
				if(tim > m * k)
					return false;
			}
		}
		return true;
	}

	LL main()
	{
		scanf("%lld%lld%lld%lld", &n, &m, &k, &p);
		for(LL i = 1; i <= n; ++i)
			scanf("%lld%lld", &h[i], &a[i]);
		LL l = 0LL, r = 2333333333333333LL;
		while(l < r - 1)
		{
			LL mid = (l + r) >> 1;
			if(check(mid))
				r = mid;
			else
				l = mid;
		}
		printf("%lld", r);
		return 0;
	}
}

signed main()
{
	sxdaknoip::main();
	return 0;
}
