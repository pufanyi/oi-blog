#include <cstdio>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef long long LL;

const int maxn = 200005;

LL aa[maxn];
LL bb[maxn];
vector<LL> gou;
int in[maxn << 2];
LL Z[maxn << 2];
set<LL> ans;

int main()
{
	int n;
	LL m;
	scanf("%d%lld", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%lld", &aa[i]);
	sort(aa + 1, aa + n + 1);
	bb[1] = ((aa[1] - aa[n]) + m) % m;
	for(int i = 2; i <= n; ++i)
		bb[i] = ((aa[i] - aa[i-1]) % m + m) % m;
	for(int i = n; i; --i)
	{
		gou.push_back(bb[i]);
		in[gou.size() - 1] = i;
	}
	gou.push_back(-1LL);
	for(int i = 1; i <= n; ++i)
	{
		gou.push_back(bb[i]);
		in[gou.size() - 1] = i;
	}
	for(int i = 1; i <= n; ++i)
	{
		gou.push_back(bb[i]);
		in[gou.size() - 1] = i;
	}
	Z[0] = gou.size();
	for(int i = 1, j = 1, k; i < (int) gou.size(); i = k)
	{
		j = max(j, i);
		while(gou[j] == gou[j - i])
			++j;
		Z[i] = j - i;
		k = i + 1;
		while(k + Z[k - i] < j)
		{
			Z[k] = Z[k - i];
			++k;
		}
	}
	for(int i = 1; i < (int) gou.size(); ++i)
		if(Z[i] >= n)
			ans.insert((aa[in[i] - 1 ? in[i] - 1 : n] + aa[n]) % m);
	printf("%d\n", (int) ans.size());
	for(auto it = ans.begin(); it != ans.end(); ++it)
		printf("%lld ", *it);
	return 0;
}
