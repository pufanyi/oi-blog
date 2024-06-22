#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int n;

struct Tree
{
	int no[maxn << 2];
	int K;

	inline void build_tree()
	{
		for(K = 1; K <= n; K <<= 1);
	}

	inline void add(int k, int x)
	{
		if(!k)
			return;
		for(k += K; k; k >>= 1)
			no[k] += x;
	}

	inline int query(int l, int r)
	{
		int ans = 0;
		for(l += K - 1, r += K + 1; l ^ r ^ 1; l >>= 1, r >>= 1)
		{
			if(~l & 1)
				ans += no[l ^ 1];
			if(r & 1)
				ans += no[r ^ 1];
		}
		return ans;
	}
} tr1, tr2;

int fa[maxn], ffa[maxn], lst[maxn];

struct ask
{
	int l, r, id;

	friend bool operator < (ask a, ask b)
	{
		return a.r < b.r;
	}
} q[maxn];

int ans[maxn];

int main()
{
	scanf("%d", &n);
	tr1.build_tree(), tr2.build_tree();
	for(int i = 1, aa; i <= n; ++i)
	{
		scanf("%d", &aa);
		fa[i] = lst[aa];
		lst[aa] = i;
		ffa[i] = (fa[i] - fa[fa[i]] == i - fa[i]) ? ffa[fa[i]] : fa[fa[i]];
	}
	int Q;
	scanf("%d", &Q);
	for(int i = 1; i <= Q; ++i)
	{
		scanf("%d%d", &q[i].l, &q[i].r);
		q[i].id = i;
	}
	sort(q + 1, q + Q + 1);
	for(int i = 1, now = 0; i <= Q; ++i)
	{
		register int l = q[i].l, r = q[i].r;
		while(now < r)
		{
			now++;
			tr1.add(fa[now], -1);
			tr1.add(now, 1);
			tr2.add(ffa[fa[now]], -1);
			tr2.add(ffa[now], 1);
		}
		int tt1 = tr1.query(l, r), tt2 = tr2.query(l, r);
		ans[q[i].id] = tt1 + (tt1 == tt2);
	}
	for(int i = 1; i <= Q; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
