#include <cstdio>

typedef long long LL;

const int maxn = 2333;

LL ans[maxn];
LL p, k;

int main()
{
	scanf("%lld%lld", &p, &k);
	int top = 0;
	while(p)
	{
		ans[++top] = p % (-k);
		p /= -k;
		if(ans[top] < 0)
			p++, ans[top] += k;
	}
	printf("%d\n", top);
	for(int i = 1; i <= top; ++i)
		printf("%d ", ans[i]);
	return 0;
}