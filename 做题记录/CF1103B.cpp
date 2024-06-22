#include <cstdio>
#include <map>

using namespace std;

map<pair<int, int>, int> mp;

char ask[23];

inline bool print(int x, int y)
{
	if(x == y)
		return x;
	if(mp.find(make_pair(x, y)) != mp.end())
		return mp[make_pair(x, y)];
	printf("? %d %d\n", x, y);
	fflush(stdout);
	scanf("%s", ask);
	bool ans = (ask[0] == 'x');
	mp[make_pair(x, y)] = ans;
	mp[make_pair(y, x)] = !ans;
	return ans;
}

inline void print(int x)
{
	if(!x)
		x++;
	printf("! %d\n", x);
	fflush(stdout);
}

inline void solve()
{
	mp.clear();
	int x = 0, y = 1;
	while(true)
	{
		if(print(x, y))
			break;
		else
			x = y, y <<= 1;
	}
	int l = x, r = y;
	while(l < r)
	{
		int mid = (l + r) >> 1;
		if(print(mid, x))
			l = mid + 1;
		else
			r = mid;
	}
	print(l);
}

int main()
{
	char s[23];
	while(scanf("%s", s) == 1 && s[0] == 's')
		solve();
	return 0;
}
