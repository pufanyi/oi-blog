#include <fstream>
#include <iostream>
#include <queue>

using namespace std;

//ifstream fin("chess.in");
//ofstream fout("chess.out");

#define fin cin
#define fout cout

int mp[2003][2003];
int ans[600];

const int mod = 1e9+7;

int dirx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int diry[] = {2, -2, 2, -2, 1, -1, 1, -1};

struct sxd
{
    int x, y;
};

queue<sxd> Q;

int n;
long long k;
long long cnt;

inline void bfs(int x, int y)
{
    mp[x][y] = 1;
    Q.push((sxd){x, y});
    while(!Q.empty())
    {
        sxd tmp = Q.front();
        Q.pop();
        ans[mp[tmp.x][tmp.y]]++;
        if(ans[mp[tmp.x][tmp.y]] == mod) ans[mp[tmp.x][tmp.y]] = 0;
        if(mp[tmp.x][tmp.y] > k+1 || mp[tmp.x][tmp.y] > 500)
            break;
        for(int i = 0; i < 8; ++i)
        {
            int tx = tmp.x + dirx[i];
            int ty = tmp.y + diry[i];
            if(mp[tx][ty]) continue;
            mp[tx][ty] = mp[tmp.x][tmp.y] + 1;
            Q.push((sxd){tx, ty});
        }
    }
}

signed main()
{
    fin >> k >> n;
    for(int i = 1, x, y; i <= n; ++i)
    {
        fin >> x >> y;
        x += 1001;
        y += 1001;
        mp[x][y] = 1;
    }
    bfs(1001, 1001);
    if(k < 500)
    {
        for(int i = 1; i <= k+1; ++i)
            cnt = (cnt+ans[i])%mod;
        fout << cnt << endl;
    }
    else
    {
        long long inc = ans[500] - ans[499];
        k -= 498;
        k %= mod;
        for(int i = 0; i <= 499; ++i)
            cnt = (cnt+ans[i])%mod;
        fout << (((k*ans[500]%mod+cnt)%mod+(k*(k-1)>>1)%mod*inc%mod)%mod+mod)%mod << endl;
    }
    return 0;
}