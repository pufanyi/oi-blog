#include <cstdio>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100005;
const int inf = 0x3f3f3f3f;

typedef pair<int, int> pii;

namespace sxdaknoip
{
	int n, k;
	int aa[maxn];
	pii dmin[maxn];
	pii dmax[maxn];
	int lmin;
	int lmax;
	int rmin;
	int rmax;
	int cntans;
	pii anss[maxn];

	int main()
	{
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; ++i)
			scanf("%d", &aa[i]);
		int ans = 0;
		lmin = lmax = 1;
		rmin = rmax = 0;
		for(int l = 1, r = 0; l <= n && r <= n; ++l)
		{
			while(lmax <= rmax && dmax[lmax].second < l)
				lmax++;
			while(lmin <= rmin && dmin[lmin].second < l)
				lmin++;
			int maxx = lmax <= rmax ? dmax[lmax].first : 0;
			int minn = lmin <= rmin ? dmin[lmin].first : inf;
			while(r < n && max(maxx, aa[r + 1]) - min(minn, aa[r + 1]) <= k)
			{
				r++;
				while(lmax <= rmax && dmax[rmax].first <= aa[r])
					rmax--;
				dmax[++rmax] = make_pair(aa[r], r);
				while(lmin <= rmin && dmin[rmin].first >= aa[r])
					rmin--;
				dmin[++rmin] = make_pair(aa[r], r);
				maxx = dmax[lmax].first;
				minn = dmin[lmin].first;
			}
			if(r - l + 1 > ans)
			{
				ans = r - l + 1;
				cntans = 1;
				anss[cntans] = make_pair(l, r);
			}
			else if(r - l + 1 == ans)
				anss[++cntans] = make_pair(l, r);
		}
		printf("%d %d\n", ans, cntans);
		for(int i = 1; i <= cntans; ++i)
			printf("%d %d\n", anss[i].first, anss[i].second);
		return 0;
	}
}

int main()
{
	sxdaknoip::main();
	return 0;
}
