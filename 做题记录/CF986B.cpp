#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int maxn = 1000005;

int aa[maxn];

int main()
{
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &aa[i]);
	int ans = 0;
	for(int i = 1; i <= n; ++i)
	{
		while(aa[i] != i)
		{
			swap(aa[aa[i]], aa[i]);
			ans++;
		}
	}
	if((n & 1) == (ans & 1))
		puts("Petr");
	else
		puts("Um_nik");
	return 0;
}
