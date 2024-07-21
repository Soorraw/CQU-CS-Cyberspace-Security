#define push_back pb
#define first fst
#define second sec
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef array<int,3> ai3;
typedef array<ll,3> al3;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef double db;
const int N=1e5+10,M=11,inf=0x3f3f3f3f,mod=1e9+7;//998244353;
const ll inff=0x3f3f3f3f3f3f3f3f;
const db eps=1e-9;


void solve()
{
	int n=3;
	string s=" UZ QSO VUOHXMOPV GPOZPEVSG ZWSZ OPFPESX \
UDBMETSX AIZ VUEPHZ HMDZSHZO WSFP APPD TSVP QUZW YMXUZUHSX \
EPYEPOPDZSZUFPO MB ZWP FUPZ HMDJ UD TMOHMQ";
	vector<map<string,int>>mp(n+1); 
	vi cnt(n+1);
	int m=s.size();
	for(int i=1;i<=n;i++)
	for(int l=1,r=i;r<m;l++,r++)
	{
		auto x=s.substr(l,i);
		if(x.find(' ')==x.npos)
		{
			mp[i][x]++;//mp[i][x]统计的是长度为i的只含可打印字符的子段x在密文中出现的次数
			cnt[i]++;//cnt[i]统计的是长度为i的子段数 
		} 
	}
	vector<vector<pair<string,db>>>fq(n+1);
	for(int i=1;i<=n;i++)
	{
		for(auto [ch,x]:mp[i])
		fq[i].pb({ch,db(x)*100/cnt[i]});//计算各种子段的出现频率 
		sort(fq[i].begin(),fq[i].end(),[&](auto&x,auto&y){
			return x.sec>y.sec;//根据出现频率从大到小排序 
		});
		cout<<"|S| = "<<i<<":\n";
		for(auto [ch,x]:fq[i])
		cout<<ch<<' '<<x<<"%\n";
		cout<<'\n';
	}
	
	map<char,char>rp={//替换密码表，通过不断调整该表并观察下方打印程序的输出结果来判断替换规则的正确性
		{'Z','t'},{'W','h'},{'P','e'},{'S','a'},
		{'F','v'},{'U','i'},{'Q','w'},{'O','s'},
		{'D','n'},{'A','b'},{'I','u'},{'E','r'},
		{'X','l'},{'Y','p'},{'M','o'},{'H','c'},
		{'V','d'},{'T','m'},{'G','y'},{'B','f'},
		{'J','g'},
	};
	for(int i=1;i<m;i++)
	if(rp.count(s[i]))
	cout<<rp[s[i]];//输出文本,对于替换密码表中出现的替换输出明文文本,否则输出密文文本 
	else cout<<s[i];
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int T=1;
//	cin>>T;
//	T=read();
	while(T--)
	solve();
	return 0;
}
