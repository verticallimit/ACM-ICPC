回文树能做到如下几点：
1.求串S前缀0~i内本质不同回文串的个数（两个串长度不同或者长度相同且至少有一个字符不同便是本质不同）
2.求串S内每一个本质不同回文串出现的次数
3.求串S内回文串的个数（其实就是1和2结合起来）
4.求以下标i结尾的回文串的个数

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005 ;
const int N = 26 ;

int ans;

struct Palindromic_Tree {
	int next[MAXN][N] ;//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成
	int fail[MAXN] ;//fail指针，失配后跳转到fail指针指向的节点
	int cnt[MAXN] ;
	int num[MAXN] ;
	int len[MAXN] ;//len[i]表示节点i表示的回文串的长度
	int S[MAXN] ;//存放添加的字符
	int last ;//指向上一个字符所在的节点，方便下一次add
	int n ;//字符数组指针
	int p ;//节点指针

	int newnode ( int l ) {//新建节点
		for ( int i = 0 ; i < N ; ++ i ) next[p][i] = 0 ;
		cnt[p] = 0 ;
		num[p] = 0 ;
		len[p] = l ;
		return p ++ ;
	}

	void init () {//初始化
		p = 0 ;
		newnode (  0 ) ;
		newnode ( -1 ) ;
		last = 0 ;
		n = 0 ;
		S[n] = -1 ;//开头放一个字符集中没有的字符，减少特判
		fail[0] = 1 ;
	}

	int get_fail ( int x ) {//和KMP一样，失配后找一个尽量最长的
		while ( S[n - len[x] - 1] != S[n] ) x = fail[x] ;
		return x ;
	}

	void add ( int c ) {
		c -= 'a' ;
		S[++ n] = c ;
		int cur = get_fail ( last ) ;//通过上一个回文串找这个回文串的匹配位置
		if ( !next[cur][c] ) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串
			int now = newnode ( len[cur] + 2 ) ;//新建节点
			fail[now] = next[get_fail ( fail[cur] )][c] ;//和AC自动机一样建立fail指针，以便失配后跳转
			next[cur][c] = now ;
			num[now] = num[fail[now]] + 1 ;
			ans++;
		}
		last = next[cur][c] ;
		cnt[last] ++ ;
	}

	void count () { //相同回文串出现的次数
		for ( int i = p - 1 ; i >= 0 ; -- i ) cnt[fail[i]] += cnt[i] ;
		//父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！
	}
} ;

char str[MAXN] = {0};

int main() {
    int T, tcase = 1;
    scanf("%d", &T);
    while (tcase <= T) {
        ans = 0;
        scanf("%s", str);
        int len = strlen(str);
        Palindromic_Tree pt;
        pt.init();
        for (int i = 0; i < len; i++) {
            pt.add(str[i]);
        }
        printf("Case #%d: %d\n", tcase++, ans);
    }
    return 0;
}

//南京网络赛 求本质不同回文串的十进制值的累加和
#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
LL calc(int x, int y);
int n;
const LL mod = 1e9+7;

// 回文树部分

const int maxn = 2000010 ;
const int ALP = 10;

int tot[maxn],num[maxn],len[maxn],fail[maxn],S[maxn],ch[maxn][ALP];
char s[maxn];
int p,last,cnt;
LL ans;
int newnode(int l){
    tot[p]=0; num[p]=0; len[p]=l;
    return p++;
}
void init(){
    p=0; memset(ch,0,sizeof(ch));
    newnode(0); newnode(-1);
    last=0; cnt=0; S[cnt]=-1; fail[0]=1;
}
int get_fail(int x){
    while(S[cnt-len[x]-1]!=S[cnt]) x=fail[x];
    return x;
}
void add(int c,int pos){
    S[++cnt]=c;
    int cur=get_fail(last);
    if (!ch[cur][c]){
        int now=newnode(len[cur]+2);
        fail[now]=ch[get_fail(fail[cur])][c];
        ch[cur][c]=now;
        ans += calc(pos + 1 - (len[cur] + 2) + 1, pos + 1);
        ans %= mod;
    }
    last=ch[cur][c];
    tot[last]++;
}

// 计算值部分

char str[maxn] = {0};

long long sum[maxn] = {0};
long long pw[maxn] = {0};
long long pww[maxn] = {0};

LL calc(int x, int y) {
    y++;
    if (y > n) sum[y] = 0;
    LL temp = (((sum[x] - sum[y]) + mod) % mod) * pww[n-y+1];
    LL w = (temp + mod) % mod;
    return w;
}

long long quickpow(long long a, long long b) {
    if (b < 0) return 0;
    long long ret = 1;
    a %= mod;
    while(b) {
        if (b & 1) ret = (ret * a) % mod;
        b >>= 1;
        a = (a * a) % mod;
    }
    return ret;
}
long long inv(long long a) {
    return quickpow(a, mod - 2);
}

void _init() {
    LL len = strlen(str);
    LL pp = 1;
    sum[len + 1] = 0;
    sum[len] = 0;
    for (LL i = len - 1; i >= 0; i--) {
        sum[i + 1] = (((str[i] - '0') * pp) % mod + sum[i + 1 + 1]) % mod;
        pp = (pp * 10) % mod;
    }
    pw[0] = 1;
    pww[0] = inv(pw[0]);
    for (LL i = 1; i < maxn; i++) {
        pw[i] = (pw[i - 1] * 10) % mod;
        pww[i] = inv(pw[i]);
    }
}

int main() {
    ans = 0;
    scanf("%s", str);
    _init();
    int len = strlen(str);
    n = len;
    init();
    for (int i = 0; i < len; i++) {
        add(str[i] - '0', i);
    }
    printf("%lld\n", ans % mod);
    return 0;
}
