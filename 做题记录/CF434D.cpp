#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const LL maxn = 10005;
const LL maxm = 5000005;
const LL inf = 0x3f3f3f3f3f3f3f3f;
const LL lim = 1000000000000;

struct Edge
{
	LL to, nxt, cap;
} e[maxm << 1];

LL first[maxn], first_bak[maxn];

inline void add_edge(LL from, LL to, LL cap)
{
	static LL cnt = -1;
	e[++cnt].nxt = first[from];
	first[from] = cnt;
	e[cnt].to = to;
	e[cnt].cap = cap;
	e[++cnt].nxt = first[to];
	first[to] = cnt;
	e[cnt].to = from;
	e[cnt].cap = 0;
}

LL n, m, S, T;

LL bh[105][205];
LL a[maxn], b[maxn], c[maxn];
LL ll[maxn];
LL rr[maxn];
LL dep[maxn];

inline LL getans(LL I, LL x)
{
	return a[I] * x * x + b[I] * x + c[I];
}

inline bool bfs()
{
	memset(dep, 0x3f, sizeof(dep));
	queue<LL> q;
	q.push(S);
	dep[S] = 0;
	for(int i = S; i <= T; ++i)
		first[i] = first_bak[i];
	while(!q.empty())
	{
		LL now = q.front();
		q.pop();
		for(int i = first[now]; ~i; i = e[i].nxt)
		{
			LL to = e[i].to;
			if(dep[to] >= inf && e[i].cap > 0)
			{
				dep[to] = dep[now] + 1;
				q.push(to);
			}
		}
	}
	return dep[T] < inf;
}

inline LL dfs(LL now, LL lim)
{
	if(!lim || now == T)
		return lim;
	LL flow = 0;
	for(int i = first[now]; ~i; i = e[i].nxt)
	{
		first[now] = i;
		register LL to = e[i].to, f;
		if(dep[to] == dep[now] + 1 && (f = dfs(to, min(lim, e[i].cap))) > 0)
		{
			lim -= f;
			flow += f;
			e[i].cap -= f;
			e[i ^ 1].cap += f;
			if(lim <= 0)
				break;
		}
	}
	return flow;
}

inline LL dinic()
{
	LL flow = 0;
	while(bfs())
		flow += dfs(S, inf);
	return flow;
}

signed main()
{
	memset(first, 0xff, sizeof(first));
	scanf("%lld%lld", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%lld%lld%lld", &a[i], &b[i], &c[i]);
	for(int i = 1; i <= n; ++i)
	{
		scanf("%lld%lld", &ll[i], &rr[i]);
		add_edge(S, T + 1, inf);
		for(LL j = ll[i] + 100; j <= rr[i] + 101; ++j)
		{
			bh[i][j] = ++T;
			if(j != ll[i] + 100)
				add_edge(bh[i][j - 1], bh[i][j], lim - getans(i, j - 1 - 100));
		}
	}
	T++;
	for(LL i = 1; i <= n; ++i)
		add_edge(bh[i][rr[i] + 101], T, inf);
	for(int i = 1, u, v, d; i <= m; ++i)
	{
		scanf("%d%d%d", &u, &v, &d);
		for(int j = ll[u]; j <= rr[u] + 1; ++j)
			if(ll[v] <= j - d && j - d <= rr[v] + 1)
				add_edge(bh[u][j + 100], bh[v][j - d + 100], inf);
	}
	for(int i = S; i <= T; ++i)
		first_bak[i] = first[i];
	printf("%lld\n", n * lim - dinic());
	return 0;
}
