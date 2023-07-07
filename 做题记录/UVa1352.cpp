#include <map>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int rot[25][6];
int rrrr[6] = {0, 4, 1, 2, 3, 5}; // ->
int up[6] = {1, 5, 2, 0, 4, 3}; // ^
int zheng[6] = {0, 1, 2, 3, 4, 5};
int zz[6] = {2, 0, 1, 5, 4, 3};

inline void rotate(int* x, int* k)
{
	int ans[6];
	for(int i = 0; i < 6; ++i)
		ans[i] = x[k[i]];
	for(int i = 0; i < 6; ++i)
		x[i] = ans[i];
}

inline void pre()
{
	int now[] = {0, 1, 2, 3, 4, 5};
	int cnt = 0;
	for(int i = 0; i < 6; ++i)
	{
		switch(i)
		{
			case 1:
				rotate(now, up);
				break;
			case 2:
				rotate(now, rrrr);
				rotate(now, rrrr);
				rotate(now, rrrr);
				rotate(now, up);
				break;
			case 3:
				rotate(now, up);
				rotate(now, up);
				rotate(now, up);
				break;
			case 4:
				rotate(now, rrrr);
				rotate(now, up);
				break;
			case 5:
				rotate(now, up);
				rotate(now, up);
				break;
		}
		for(int j = 0; j < 4; ++j)
		{
			cnt++;
			for(int k = 0; k < 6; ++k)
				rot[cnt][k] = now[k];
			rotate(now, rrrr);
		}
		for(int j = 0; j < 6; ++j)
			now[j] = zheng[j];
	}
}

map<string, int> mp;
int zfx[5][6];

inline void read(int n)
{
	string s;
	mp.clear();
	for(int i = 1, cnt = 0; i <= n; ++i)
	{
		for(int j = 0; j < 6; ++j)
		{
			cin >> s;
			if(mp[s])
				zfx[i][j] = mp[s];
			else
				zfx[i][j] = mp[s] = ++cnt;
		}
		rotate(zfx[i], zz);
	}
}

int now_zfx[5][6];
int ans;
int N;

inline int pan()
{
	int mpp[25];
	int ans = 0;
	for(int i = 0; i < 6; ++i)
	{
		int anss = 0;
		memset(mpp, 0, sizeof(mpp));
		for(int j = 1; j <= N; ++j)
			mpp[now_zfx[j][i]]++;
		for(int j = 0; j < 25; ++j)
			anss = max(anss, mpp[j]);
		ans += N - anss;
	}
	return ans;
}

inline void dfs(int n)
{
	if(!n)
	{
		ans = min(ans, pan());
		return;
	}
	for(int i = 1; i <= 24; ++i)
	{
		for(int j = 0; j < 6; ++j)
			now_zfx[n][j] = zfx[n][j];
		rotate(now_zfx[n], rot[i]);
		dfs(n - 1);
	}
}

inline int solve(int n)
{
	ans = 0x3f3f3f3f;
	for(int j = 0; j < 6; ++j)
		now_zfx[n][j] = zfx[n][j];
	dfs(n - 1);
	return ans;
}

int main()
{
	pre();
	while(scanf("%d", &N) == 1 && N)
	{
		read(N);
		printf("%d\n", solve(N));
	}
	return 0;
}