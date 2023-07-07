#include <cstdio>
#include <map>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <sstream>
#include <iostream>

using namespace std;

map<string, int> Dp;
set<string> DEF;

// return 1 : 这个宏完全安全，以任何方式使用该宏都没问题。
// return 2 : 这个宏不安全，只要表达式中出现该宏，都会导致表达式不安全。
// return 3 : 这个宏部分安全，仅当这个宏与'*','/'连接时，或出现在'-'后面时，才会使表达式不安全。
// return 4 : 这个宏部分安全，仅当这个宏出现在'/'后面时，才会使表达式不安全。

#define islit(a) (isalpha(a) || isdigit(a))
#define calc_fu(c) (c == '+' || c == '-' || c == '*' || c == '/')

inline int dp(string s)
{
	// 删除空格
	string TMP = "";
	for(int i = 0; i < (int) s.length(); ++i)
		if(s[i] != ' ')
			TMP.push_back(s[i]);
	s = TMP;

	//建立s的副本
	string bak = s;

	// 现在map中找
	if(Dp.find(s) != Dp.end())
		return Dp[s];

	// 无运算符号的特判
	bool FLAG = true;
	for(int i = 0; i < (int) s.length(); ++i)
	{
		if(calc_fu(s[i]) || s[i] == '(' || s[i] == ')')
		{
			FLAG = false;
			break;
		}
	}
	if(FLAG)
		return Dp[s] = 1;

	// 找到最后一位运算符
	typedef pair<char, int> pci;
	stack<pci> sta;
	while(!sta.empty())
		sta.pop();
	for(int i = 0; i < (int) s.length(); ++i)
	{
		if(s[i] == ')')
		{
			char Tmp;
			do
			{
				Tmp = sta.top().first;
				sta.pop();
			}
			while(Tmp != '(');
			sta.push(make_pair('1', i));
		}
		else if(islit(s[i]) && (sta.empty() || !islit(sta.top().first)))
			sta.push(make_pair(s[i], i));
		else if(calc_fu(s[i]) || s[i] == '(')
			sta.push(make_pair(s[i], i));
	}
	if(sta.size() == 1)
	{
		s = s.substr(1, s.length() - 2);
		return Dp[bak] = (dp(s) == 2 ? 2 : 1);
	}
	stack<pci> str_sta;
	while(!str_sta.empty())
		str_sta.pop();
	while(!sta.empty())
	{
		str_sta.push(sta.top());
		sta.pop();
	}
	int last_place = 0;
	while(!str_sta.empty())
	{
		pci now = str_sta.top();
		str_sta.pop();
		if(islit(now.first))
		{
			if(!sta.empty() && (sta.top().first == '*' || sta.top().first == '/'))
			{
				last_place = sta.top().second;
				sta.pop();
			}
			else
				sta.push(now);
		}
		else if(calc_fu(now.first))
			sta.push(now);
	}
	while(!sta.empty())
	{
		if(calc_fu(sta.top().first))
		{
			last_place = sta.top().second;
			break;
		}
		sta.pop();
	}

	// dp
	int L = 0, R = 0;
	if((L = dp(bak.substr(0, last_place))) == 2 || (R = dp(bak.substr(last_place + 1))) == 2)
		return Dp[bak] = 2;
	switch(bak[last_place])
	{
		case '+':
			return Dp[bak] = 3;
		case '-':
			if(R == 3)
				return Dp[bak] = 2;
			else
				return Dp[bak] = 3;
		case '*':
			if(L == 3 || R == 3)
				return Dp[bak] = 2;
			else
				return 4;
		case '/':
			if(L == 3 || R == 3 || R == 4)
				return Dp[bak] = 2;
			else
				return 4;
	}
	return 0;
}

int main()
{
	int n;
	cin >> n;
	Dp.clear();
	DEF.clear();
	string a;
	getline(cin, a);
	for(int i = 1; i <= n; ++i)
	{
		string def, defa;
		while(cin >> def && def != "define" && def != "#define");
		cin >> defa;
		if(DEF.count(defa))
		{
			puts("Suspicious");
			return 0;
		}
		getline(cin, a);
		Dp[defa] = dp(a);
		DEF.insert(defa);
	}
	getline(cin, a);
	if(dp(a) == 2)
		puts("Suspicious");
	else
		puts("OK");
	return 0;
}
