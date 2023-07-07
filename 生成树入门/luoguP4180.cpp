// luogu-judger-enable-o2
#include <cstdio>
#include <cstring>
#include <cstdlib> // bebug
#include <iostream> // debug
#include <algorithm>

typedef long long LL;

inline char gc()
{
	static char buf[1<<12],*p1=buf,*p2=buf;
	return (p1==p2)&&(p2=(p1=buf)+fread(buf,1,1<<12,stdin),p1==p2)?EOF:*p1++;
}

#define dd c = gc()
inline void read(int& x)
{
	x = 0;
	int dd;
	bool f = false;
	for(; !isdigit(c); dd)
		if(c == '-')
			f = true;
	for(; isdigit(c); dd)
		x = (x<<1) + (x<<3) + (c^48);
	if(f)
		x = -x;
}
#undef dd

using std::min;
using std::max;
using std::sort;

using std::cin; // debug
using std::cout; // debug
using std::endl; // debug

const int maxn = 100005;
const int maxm = 300005;
const LL inf = 0x3f3f3f3f3f3f3f3f;

int n, m;
LL mst;
LL ans = inf;

struct Edge
{
	int from, to;
	int dist;

	inline bool operator < (const Edge& other) const
	{
		return this->dist < other.dist;
	}
} e[maxm];

bool xuan[maxm];

namespace sp // edge tree
{
	struct Edge
	{
		int to, nxt;
		int dist;
	} e[maxm<<1];

	int first[maxn];

	int cnt = 0;

	inline void add_edge(int from, int to, int dist)
	{
		e[++cnt].nxt = first[from];
		first[from] = cnt;
		e[cnt].to = to;
		e[cnt].dist = dist;
		e[++cnt].nxt = first[to];
		first[to] = cnt;
		e[cnt].to = from;
		e[cnt].dist = dist;
	}
}

namespace KK // build tree
{
	int fa[maxn];

	inline void pre()
	{
		for(int i = 1; i <= ::n; ++i)
			fa[i] = i;
	}

	inline int getfa(int x)
	{
		return fa[x] == x ? x : fa[x] = getfa(fa[x]);
	}

	inline void Kruskal()
	{
		sort(::e + 1, ::e + ::m + 1);
		::mst = 0;
		int cnt = 1;
		for(int i = 1; i <= ::m && cnt < ::n; ++i)
		{
			int faf = getfa(::e[i].from);
			int fat = getfa(::e[i].to);
			if(faf != fat)
			{
				fa[faf] = fat;
				::xuan[i] = true;
				sp::add_edge(::e[i].from, ::e[i].to, ::e[i].dist);
				cnt++;
				::mst += ::e[i].dist;
			}
		}
	}

	inline void build_tree()
	{
		pre();
		Kruskal();
	}
}

namespace sp // shupou
{
	int fa[maxn];
	LL qz[maxn];
	int siz[maxn];
	int son[maxn];
	int dep[maxn];

	inline void dfs1(int now)
	{
		siz[now] = 1;
		for(int i = first[now]; i; i = e[i].nxt)
		{
			int to = e[i].to;
			if(fa[now] != to)
			{
				fa[to] = now;
				qz[to] = e[i].dist;
				dep[to] = dep[now] + 1;
				dfs1(to);
				siz[now] += siz[to];
				if(!son[to] || siz[to] > siz[son[now]])
					son[now] = to;
			}
		}
	}

	LL dfsx[maxn];
	int ffa[maxn];
	int ll[maxn];
	int cntt;

	inline void dfs2(int now)
	{
//		cout << now << endl;
		dfsx[++cntt] = qz[now];
		ll[now] = cntt;
		if(son[now])
		{
			ffa[son[now]] = ffa[now];
			dfs2(son[now]);
		}
		for(int i = first[now]; i; i = e[i].nxt)
		{
			int to = e[i].to;
			if(fa[now] != to && son[now] != to)
			{
				ffa[to] = to;
				dfs2(to);
			}
		}
	}

	struct Node
	{
		LL zdz;
		LL cdz;

		friend Node operator + (Node a, Node b)
		{
			Node ans;
			ans.zdz = max(a.zdz, b.zdz);
			ans.cdz = max(a.cdz, b.cdz);
			if(a.zdz != b.zdz)
				ans.cdz = max(min(a.zdz, b.zdz), ans.cdz);
			return ans;
		}
	};

#define ls(x) (x<<1)
#define rs(x) (x<<1|1)
	struct Tree
	{
		Node no[maxn<<2];

		inline void push_up(int k)
		{
			no[k] = no[ls(k)] + no[rs(k)];
		}

		inline void build_tree(int l, int r, int k)
		{
			if(l == r)
			{
				no[k].cdz = -inf;
				no[k].zdz = dfsx[l];
				return;
			}
			int mid = (l + r) >> 1;
			build_tree(l, mid, ls(k));
			build_tree(mid+1, r, rs(k));
			push_up(k);
		}

		inline Node query(int l, int r, int k, int L, int R)
		{
//			cout << l << ' ' << r << ' ' << k << ' ' << L << ' ' << R << endl;
			if(L <= l && r <= R)
				return no[k];
			int mid = (l + r) >> 1;
			if(R <= mid)
				return query(l, mid, ls(k), L, R);
			if(L > mid)
				return query(mid+1, r, rs(k), L, R);
			return query(l, mid, ls(k), L, R) + query(mid+1, r, rs(k), L, R);
		}
	} tr;
#undef ls
#undef rs

	inline void pre()
	{
		dfs1(1);
		fa[1] = ffa[1] = 1;
		dfs2(1);
		tr.build_tree(1, n, 1);
//		for(int i = 1; i <= n; ++i)
//			cout << dfsx[i] << ' ';
//		cout << endl;
//		system("pause");
	}

	inline void query(int a, int b, LL d)
	{
		Node ans;
		ans.cdz = ans.zdz = -inf;
		while(ffa[a] != ffa[b])
		{
//			cout << a << ' ' << b << endl;
//			cout << ffa[a] << ' ' << ffa[b] << endl;
//			cout << ffa[2] << ' ' << ffa[4] << endl;
			if(dep[ffa[a]] > dep[ffa[b]])
			{
				ans = ans + tr.query(1, n, 1, ll[ffa[a]], ll[a]);
//				cout << ll[ffa[a]] << ' ' << ll[a] << endl;
//				cout << a << ' ' << tr.query(1, n, 1, ll[ffa[a]], ll[a]).zdz << ' ' << tr.query(1, n, 1, ll[ffa[a]], ll[a]).cdz << endl;
				a = fa[ffa[a]];
			}
			else
			{
				ans = ans + tr.query(1, n, 1, ll[ffa[b]], ll[b]);
//				cout << ll[ffa[b]] << ' ' << ll[b] << endl;
//				cout << b << ' ' << tr.query(1, n, 1, ll[ffa[b]], ll[b]).zdz << ' ' << tr.query(1, n, 1, ll[ffa[b]], ll[b]).cdz << endl;
				b = fa[ffa[b]];
			}
		}
//		cout << a << ' ' << b << ' ' << d << ' ' << ans.zdz << ' ' << ans.cdz << endl;
		if(a != b)
			ans = ans + tr.query(1, n, 1, min(ll[a], ll[b]) + 1, max(ll[a], ll[b]));
//		cout << ans.cdz << ' ' << ans.zdz << endl;
		if(d <= ans.zdz)
			::ans = min(::ans, d - ans.cdz);
		else
			::ans = min(::ans, d - ans.zdz);
	}
}

signed main()
{
//	freopen("1977.in", "r", stdin);
//	freopen("1977.out", "w", stdout);
//	sp::deb();
	read(n);
	read(m);
	for(int i = 1; i <= m; ++i)
	{
		read(e[i].from);
		read(e[i].to);
		read(e[i].dist);
	}
	KK::build_tree();
	sp::pre();
	for(int i = 1; i <= m; ++i)
	{
		if(!xuan[i])
		{
			sp::query(e[i].from, e[i].to, e[i].dist);
//			cout << i << ' ' << ans << ' ' << e[i].dist << endl;
//			for(int i = 1; i <= 100000; ++i)
//			for(int j = 1; j <= 1000; ++j);
		}
	}
//	cout << ans << endl;
	printf("%lld", mst + ans);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}