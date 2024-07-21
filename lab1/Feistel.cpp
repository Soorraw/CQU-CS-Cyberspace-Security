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

//IP置换 
const vi ip={
	58, 50, 42, 34, 26, 18, 10,  2,
	60, 52, 44, 36, 28, 20, 12,  4,
	62, 54, 46, 38, 30, 22, 14,  6,
	64, 56, 48, 40, 32, 24, 16,  8,
	57, 49, 41, 33, 25, 17,  9,  1,
	59, 51, 43, 35, 27, 19, 11,  3,
	61, 53, 45, 37, 29, 21, 13,  5,
	63, 55, 47, 39, 31, 23, 15,  7
};
//IP逆置换 
const vi inv={
	40,  8, 48, 16, 56, 24, 64, 32,
	39,  7, 47, 15, 55, 23, 63, 31,
	38,  6, 46, 14, 54, 22, 62, 30,
	37,  5, 45, 13, 53, 21, 61, 29,
	36,  4, 44, 12, 52, 20, 60, 28,
	35,  3, 43, 11, 51, 19, 59, 27,
	34,  2, 42, 10, 50, 18, 58, 26,
	33,  1, 41,  9, 49, 17, 57, 25	
};
//扩展变换E 
const vi e={
	32,  5,
	 4,  9,
	 8, 13,
	12, 17,
	16, 21,
	20, 25,
	24, 29,
	28,  1
};
//子密钥PC-1置换 
const vi pc1={
	57, 49, 41, 33, 25, 17,  9,
	 1, 58, 50, 42, 34, 26, 18,
	10,  2, 59, 51, 43, 35, 27,
	19, 11,  3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	 7, 62, 54, 46, 38, 30, 22,
	14,  6, 61, 53, 45, 37, 29,
	21, 13,  5, 28, 20, 12,  4
};
//子密钥PC-2置换 
const vi pc2={
	14, 17, 11, 24,  1,  5,
	 3, 28, 15,  6, 21, 10,
	23, 19, 12,  4, 26,  8,
	16,  7, 27, 20, 13,  2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32
};
//压缩置换S 
const vvi sbox={
	{
		14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
		 0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
		 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
		15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
	},
	{
		15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
		 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
		 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
		13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9,
	},
	{
		10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
		13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11,  5,  1,
		13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
		 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
	},
	{
		 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
		13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
		10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
		 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
	},
	{
		 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
		14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
		 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
		11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
	},
	{
		12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
		10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
		 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
		 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
	},
	{
		 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
		13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
		 1,  4, 11, 13, 12,  3,  7,  4, 10, 15,  6,  8,  0,  5,  9, 12,
		 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
	},
	{
		13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
		 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
		 1, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
		 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
	}
};
//P置换 
const vi p={
	16,  7, 20, 21, 29, 12, 28, 17,
	 1, 15, 23, 26,  5, 18, 31, 10,
	  2, 8, 24, 14, 32, 27,  3,  9,
	19, 13, 30,  6, 22, 11,  4, 25
};
typedef bitset<32> b32;//位图,支持位运算的01串,可以和01字符串简单的相互转换 
typedef bitset<48> b48;
typedef bitset<64> b64;
typedef vector<b64> vb64;
typedef vector<string> vstr;
typedef pair<int,string> pis;
int toInt(string s)//将01字符串转换为整数
{
	int m=s.size(),res=0;
	for(int i=0;i<m;i++)
	res=(res<<1)+s[i]-'0';
	return res;
}
string to01String(char x)//将英文字符转换为8位01字符串 
{
    string res;
    for (int i=7;i>=0;i--)
    {
        int p=(x>>i)&1;
        res.pb(p+'0');
    }
    return res;
}
string to01String(int x)//将整数变换为4位01字符串 
{
	string res;
	for(int i=0;i<4;i++)
	{
		res+=(x&1)+'0';
		x>>=1;
	}
	reverse(res.begin(),res.end());
	return res;
}
pis to01String(string s)//将明文转换为64位01字符串分组 
{
	string res;
	for(auto ch:s)
	res+=to01String(ch);
	int n=res.size(),m=(n+63)/64,k=m*64-n;//分组数m向上取整 
	if(k)
	res=string(k,'0')+res;//不足64位的高位填充0 
	return {m,res};
}
char toChar(string s)//将8位01字符串转换为英文字符 
{
	char res=0;
	for(int i=0;i<8;i++)
	res=(res<<1)+s[i]-'0';
	return res;
}
string toString(string s)//将64位01字符串转换问明文段 
{
	string res;
	for(int i=0;i<64;i+=8)
	res+=toChar(s.substr(i,8));
	return res;
}
vstr grouping(string s)//明文分组 
{
	auto [m,p]=to01String(s);//将明文转换为若干组64位01字符串,每8位代表一个英文字符 
	vstr res;
	for(int i=1,j=0;i<=m;i++,j+=64)
	res.pb(p.substr(j,64));
	return res;
}
const string key=to01String("Arknight").sec;//64位密钥 
string PC1(string s)//PC-1子密钥生成置换 
{
	string res;
	for(int i=0;i<56;i++)
	res+=s[pc1[i]-1];
	return res;
}
string PC2(string s)//PC-2子密钥生成置换 
{
	string res;
	for(int i=0;i<48;i++)
	res+=s[pc2[i]-1];
	return res;
}
string K(string c,string d,int r)//子密钥生成算法 
{
	string ci=c.substr(r)+c.substr(0,r);//第r轮循环左移r位 
	string di=d.substr(r)+d.substr(0,r);
	return PC2(ci+di);
}
string IP(string s)//IP置换 
{
	string res;
	res.resize(64);
	for(int i=0;i<64;i++)
	res[i]=s[ip[i]-1];
	return res;
}
string invIP(string s)//IP逆置换 
{
	string res;
	res.resize(64);
	for(int i=0;i<64;i++)
	res[i]=s[inv[i]-1];
	return res;
}
string E(string s)//扩展变换E 
{
	//与密钥无关的纯位移置换
	//32位分为8组: 每组4位,经E置换后,变成每组6位
	string res;
	for(int i=0,j=0;i<32;i+=4,j+=2)
	res+=s[e[j]-1]+s.substr(i,4)+s[e[j+1]-1];
	return res;
}
string S(string s)//压缩变换S 
{
	//共8个S盒,每盒输入6位,输出4位
	string res;
	for(int i=0,j=0;j<8;i+=6,j++)
	{
		string x=s.substr(i,6);//6位输入B1B2B3B4B5B6 
		int nx=toInt(x.substr(0,1)+x.substr(5,1));//B1B6为S盒行坐标 
		int ny=toInt(x.substr(1,4));//B2B3B4B5为S盒列坐标 
		res+=to01String(sbox[j][nx*16+ny]);
	}
	return res;
}
string P(string s)//P置换 
{
	string res;
	for(int i=0;i<32;i++)
	res+=s[p[i]-1];
	return res;	
}
void F(string&l,string&r,string&c,string&d,int i)//F函数 
{
	string ri=(b48(E(r))^b48(K(c,d,i))).to_string();//将扩展运算E后的48位Ri与48位子密钥Ki按位异或 
	ri=P(S(ri));//将48位Ri压缩变换S为32位,并进行P置换 
	string p=l;
	l=r;//Li = Ri-1
	r=(b32(p)^b32(ri)).to_string();//将Ri与Li-1按位异或 
}
string encode(string s)//分组加密 
{
	string lr=IP(s);//IP置换 
	string l=lr.substr(0,32),r=lr.substr(32,32);
	string cd=PC1(key);
	string c=cd.substr(0,28),d=cd.substr(28,28);
	for(int i=1;i<=16;i++)
	F(l,r,c,d,i);//16轮变换 
	return r+l;
}
string decode(string s)//分组解密 
{
	string l=s.substr(0,32),r=s.substr(32,32);
	string cd=PC1(key);
	string c=cd.substr(0,28),d=cd.substr(28,28);
	for(int i=16;i;i--)
	F(l,r,c,d,i);//16轮变换 
	return invIP(r+l);//IP逆置换 
}
void solve()
{
	string plainText="CQUINFORMATIONSECURITYEXP";
	cout<<"PlainText: "+plainText+"\n\nEncoding...\n\n";
	
	vstr plainGroups=grouping(plainText);//对明文进行分组 
	int n=plainGroups.size();
	vstr cipherGroups;
	for(int i=0;i<n;i++)
	{
		string s=plainGroups[i],es=encode(s);//对明文分组进行加密 
		cout<<"Group "<<i<<":\nPlainText: "+s+"\nCipherText: "+es<<'\n';
		cipherGroups.pb(es);
	}
	cout<<"\nDecoding...\n\n";
	string ans;
	for(int i=0;i<n;i++)
	{
		string s=cipherGroups[i],ds=decode(s);//对密文分组进行解密 
		cout<<"Group "<<i<<":\nCipherText: "+s+"\nPlainText: "+ds<<'\n';
		ans+=toString(ds);//破译后的明文 
	}
	int m=ans.size();
	for(int i=0;i<=m;i++)
	if(isprint(ans[i]))//去除分组过程中填充的不可打印字符 
	{
		cout<<"\nPlainText: "+ans.substr(i)<<'\n';
		break;
	}
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
