#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int maxn = 50005;
const int maxm = 100005;

int n, m, k;

struct Edge
{
	int from, to, dist, cc;

	inline bool operator < (const Edge& other) const
	{
		return this->dist < other.dist ||
		       (this->dist == other.dist && this->cc > other.cc);
	}
} e[maxm << 1];

int fa[maxn];
inline int getfa(int x)
{
	return fa[x] == x ? x : fa[x] = getfa(fa[x]);
}

inline bool check(int K)
{
	for(int i = 1; i <= m; ++i)
		if(!e[i].cc)
			e[i].dist += K;
	sort(e + 1, e + m + 1);
	for(int i = 0; i < n; ++i)
		fa[i] = i;
	int ans = 0;
	for(int i = 1; i <= m; ++i)
	{
		int fax = getfa(e[i].from);
		int fay = getfa(e[i].to);
		if(fax != fay)
		{
			fa[fax] = fay;
			if(!e[i].cc)
				ans++;
		}
	}
	for(int i = 1; i <= m; ++i)
		if(!e[i].cc)
			e[i].dist -= K;
//	printf("%d %d %d\n", K, ans, k);
	return ans <= k;
}

inline int Kruskal(int KK)
{
	for(int i = 1; i <= m; ++i)
		if(!e[i].cc)
			e[i].dist += KK;
	sort(e + 1, e + m + 1);
	for(int i = 0; i < n; ++i)
		fa[i] = i;
	int ans = 0;
	for(int i = 1; i <= m; ++i)
	{
		int fax = getfa(e[i].from);
		int fay = getfa(e[i].to);
		if(fax != fay)
		{
			fa[fax] = fay;
			ans += e[i].dist;
		}
	}
	return ans - k * KK;
}

int main()
{
//	freopen("necklace.in", "r", stdin);
//	freopen("necklace.out", "w", stdout);
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d%d%d", &e[i].from, &e[i].to, &e[i].dist, &e[i].cc);
	int l = -1005, r = 1005;
	while(r - l > 1)
	{
		int mid = (l + r) >> 1;
		if(check(mid))
			r = mid;
		else
			l = mid;
	}
//	printf("%d\n", l);
	int ans = Kruskal(r);
	printf("%d\n", ans);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}