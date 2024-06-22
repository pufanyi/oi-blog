#include <cctype>
#include <cstdio>

namespace IO
{
	const int maxl = 23333;
	char buf[maxl], *sss = buf, *ttt = buf;

	inline char gc()
	{
		if(sss == ttt)
		{
			ttt = (sss = buf) + fread(buf, 1, maxl, stdin);
			if(sss == ttt)
				return EOF;
		}
		return *sss++;
	}

#define dd c = gc()
	template <class T>
	inline bool read(T& x)
	{
		x = 0;
		bool f = false;
		char dd;
		for(; !isdigit(c); dd)
		{
			if(c == '-')
				f = true;
			else if(c == EOF)
				return false;
		}
		for(; isdigit(c); dd)
			x = (x << 1) + (x << 3) + (c ^ 48);
		if(f)
			x = -x;
		return true;
	}
#undef dd
}

using IO::read;

#include <set>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long LL;
typedef pair<LL, int> pii;

const int maxn = 100005;

int n, k[maxn], kx[maxn], rt;
LL dp[maxn];

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

inline void dfs(int now, int fa)
{
	set<pii> st;
	st.clear();
	dp[now] = (now != rt);
	k[now] -= (now != rt);
	for(int i = first[now]; i; i = e[i].nxt)
	{
		int to = e[i].to;
		if(fa != to)
		{
			dfs(to, now);
			st.insert(make_pair(dp[to], to));
		}
	}
	int tmp = 0;
	int tmpk = k[now];
	set<pii>::reverse_iterator it;
	for(it = st.rbegin(); tmpk && it != st.rend(); tmpk--, ++it)
	{
		dp[now] += it->first + 1;
		tmp += kx[it->second];
	}
	dp[now] += min(tmpk, tmp) << 1;
	kx[now] = max(tmpk - tmp, 0);
}

int main()
{
	read(n);
	for(int i = 1; i <= n; ++i)
		read(k[i]);
	for(int i = 1, f, t; i < n; ++i)
		read(f), read(t), add_edge(f, t);
	read(rt);
	dfs(rt, 0);
	printf("%lld\n", dp[rt]);
	return 0;
}
