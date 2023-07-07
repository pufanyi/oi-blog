#include <cstdio>
#include <set>
#include <vector>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 205;

typedef set<int>::reverse_iterator rit;
typedef set<int>::iterator lit;
typedef pair<int, int> pii;

int n;

struct Edge
{
	int to, nxt;
} e[maxn << 1];

int first[maxn];

inline void add_edge(int from, int to)
{
	static int cnt = 0;
	e[++cnt].nxt = first[from];
	first[from] = cnt;
	e[cnt].to = to;
	e[++cnt].nxt = first[to];
	first[to] = cnt;
	e[cnt].to = from;
}

int maxlen[maxn];
int maxdep[maxn];
int dep[maxn];
int fa[maxn];
int ffa[maxn];
int siz[maxn];
int son[maxn];

inline void dfs1(int now)
{
	maxdep[now] = 0;
	int cmax, maxx;
	cmax = maxx = 0;
	siz[now] = 1;
	for (int i = first[now]; i; i = e[i].nxt)
	{
		int to = e[i].to;
		if (to != fa[now])
		{
			fa[to] = now;
			dep[to] = dep[now] + 1;
			dfs1(to);
			siz[now] += siz[to];
			if (!son[now] || siz[son[now]] < siz[to])
				son[now] = to;
			int nowmax = maxdep[to] + 1;
			maxdep[now] = max(maxdep[now], nowmax);
			if (nowmax >= maxx)
			{
				cmax = maxx;
				maxx = nowmax;
			}
			else if (nowmax > cmax)
				cmax = nowmax;
		}
	}
	maxlen[now] = maxx + cmax;
}

inline void dfs2(int now)
{
	if (son[now])
	{
		ffa[son[now]] = ffa[now];
		dfs2(son[now]);
	}
	for (int i = first[now]; i; i = e[i].nxt)
	{
		int to = e[i].to;
		if (to != fa[now] && to != son[now])
		{
			ffa[to] = to;
			dfs2(to);
		}
	}
}

inline void pre()
{
	dfs1(1);
	fa[1] = ffa[1] = 1;
	dfs2(1);
}

inline int __lca(int x, int y)
{
	while (ffa[x] != ffa[y])
	{
		if (dep[ffa[x]] > dep[ffa[y]])
			x = fa[ffa[x]];
		else
			y = fa[ffa[y]];
	}
	return dep[x] < dep[y] ? x : y;
}

inline void maintain(int now)
{
	int cmax = 0, maxx = 0;
	maxdep[now] = 0;
	siz[now] = 1;
	for (int i = first[now]; i; i = e[i].nxt)
	{
		int to = e[i].to;
		if (to != fa[now])
		{
			int nowmax = maxdep[to] + 1;
			maxdep[now] = max(maxdep[now], nowmax);
			if (nowmax >= maxx)
			{
				cmax = maxx;
				maxx = nowmax;
			}
			else if (nowmax > cmax)
				cmax = nowmax;
		}
	}
	maxlen[now] = maxx + cmax;
}

inline int update(int x, int ff)
{
	int tx = x;
	maxlen[x] = -233;
	maxdep[x] = -233;
	x = fa[x];
	while (x != ff)
	{
		maintain(x);
		x = fa[x];
	}
	maintain(ff);
	int ans = maxlen[ff];
	while (tx != ff)
	{
		maintain(tx);
		tx = fa[tx];
	}
	maintain(ff);
	return ans;
}

inline int getson(int up, int dow)
{
	int lst = dow;
	while (ffa[dow] != ffa[up])
	{
		dow = fa[ffa[dow]];
		lst = ffa[dow];
	}
	if (lst != 1 && fa[lst] == up)
		return lst;
	else
		return son[up];
}

inline int get(int x, int y)
{
	int lca = __lca(x, y);
	if (lca != x && lca != y)
		return maxlen[x] * maxlen[y];
	if (lca == y)
		swap(x, y);
	return maxlen[y] * update(y, x);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1, f, t; i < n; ++i)
	{
		scanf("%d%d", &f, &t);
		add_edge(f, t);
	}
	pre();
	int ans = 0;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = i + 1; j <= n; ++j)
			ans = max(ans, get(i, j));
	}
	printf("%d\n", ans);
	return 0;
}
