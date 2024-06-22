#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 100004;
const LL inf = 0x3f3f3f3f3f3f3f3f;

int n;
int to[maxn];

#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
struct Tree
{
	LL no[maxn << 2];
	int k;

	inline void build_tree()
	{
		for(k = 1; k <= n; k <<= 1);
		memset(no, 0x3f, sizeof(no));
	}

	inline void update(int pla, LL x)
	{
		x -= (n - pla);
		for(int i = k + pla; i; i >>= 1)
			no[i] = min(no[i], x);
	}

	inline LL query(int l, int r)
	{
		LL ans = inf;
		for(l += k - 1, r += k + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
		{
			if(~l & 1)
				ans = min(ans, no[l ^ 1]);
			if(r & 1)
				ans = min(ans, no[r ^ 1]);
		}
		return ans;
	}
} tr;

int main()
{
	scanf("%d", &n);
	for(int i = 1; i < n; ++i)
		scanf("%d", &to[i]);
	tr.build_tree();
	tr.update(n, 0LL);
	LL ans = 0LL;
	for(int i = n - 1; i; --i)
	{
		LL now = tr.query(i + 1, to[i]);
		now += n - to[i];
		now += n - i;
		ans += now;
		tr.update(i, now);
	}
	printf("%lld\n", ans);
	return 0;
}
