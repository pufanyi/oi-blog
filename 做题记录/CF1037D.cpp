#include <cstdio>
#include <set>
#include <utility>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 200005;

typedef pair<int, int> pii;

set<pii> st;

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

int di[maxn];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1, f, t; i < n; ++i)
	{
		scanf("%d%d", &f, &t);
		add_edge(f, t);
	}
	st.insert(make_pair(1, 1));
	di[1] = 1;
	int cnt = 1;
	for(int i = 1; i <= n; ++i)
	{
		int now;
		scanf("%d", &now);
		if(!di[now])
		{
			puts("No");
			return 0;
		}
		set<pii>::iterator it = st.find(make_pair(di[now], now));
		if(st.begin()->first < di[now])
		{
			puts("No");
			return 0;
		}
		st.erase(it);
		++cnt;
		for(int i = first[now]; i; i = e[i].nxt)
		{
			int to = e[i].to;
			if(!di[to])
			{
				di[to] = cnt;
				st.insert(make_pair(di[to], to));
			}
		}
	}
	puts("Yes");
	return 0;
}