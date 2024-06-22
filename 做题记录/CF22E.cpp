#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 100005;

int nxt[maxn];
int vis[maxn];

inline int dfs(int x)
{
	vis[x] = true;
	if (vis[nxt[x]])
		return x;
	return dfs(nxt[x]);
}

int rd[maxn];

int main()
{
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i)
	{
		scanf("%d", &nxt[i]);
		rd[nxt[i]]++;
	}
	vector<int> ff;
	vector<int> tt;
	for (int i = 1; i <= n; ++i)
	{
		if (!rd[i])
		{
			ff.push_back(i);
			tt.push_back(dfs(i));
		}
	}
	int tmp = ff.size();
	for (int i = 1; i <= n; ++i)
	{
		if (!vis[i])
		{
			ff.push_back(i);
			tt.push_back(dfs(i));
		}
	}
	if (ff.size() == 1 && !tmp)
	{
		puts("0");
		return 0;
	}
	printf("%d\n", (int)ff.size());
	for (unsigned i = 0; i < ff.size(); ++i)
		printf("%d %d\n", tt[((i - 1) + ff.size()) % ff.size()], ff[i]);
	return 0;
}
