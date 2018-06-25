#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
#define N 15

struct Card
{
	int point;//点数，颜色
	char color;
};

struct Maxcard
{
	int point[5];//点数
	int flag;//牌型
}maxcard[N];

Card card[5];
Card Pcard[N][2];
Card Ccard[5];
int n;

bool cmp(Card a,Card b)
{
	return a.point>b.point;
}

void init()//把每个选手的最大牌先初始化为最小
{
	for(int i=0;i<n;i++)
	{
		maxcard[i].flag=10;
		maxcard[i].point[0]=7;
		maxcard[i].point[1]=5;
		maxcard[i].point[2]=4;
		maxcard[i].point[3]=3;
		maxcard[i].point[4]=2;
	}
}

int getp(char p[])
{
	int pp;
	if(strcmp(p,"10")==0)pp=10;
	else if(p[0]>='2'&&p[0]<='9')pp=p[0]-'0';
	else if(p[0]=='J')pp=11;
	else if(p[0]=='Q')pp=12;
	else if(p[0]=='K')pp=13;
	else pp=14;
	return pp;
}

Maxcard gettype(Card select[5])
{
	sort(select,select+5,cmp);
	bool samec=true;
	bool isstr=true;
	int i;
	for(i=1;i<5;i++)//判断同花和顺子
	{
		if(select[i].color!=select[i-1].color)samec=false;
		if(select[i].point!=select[i-1].point-1)isstr=false;
	}
	if(select[0].point==14&&select[1].point==5&&select[2].point==4&&select[3].point==3&&select[4].point==2)//A2345的情况
	{
		isstr=true;
		for(i=0;i<4;i++)select[i].point=select[i+1].point;
		select[4].point=1;
	}
	Maxcard ret;
	for(i=0;i<5;i++)ret.point[i]=select[i].point;
	int vis[15]={0};
	int maxsame=0,secsame=0,maxi;
	for(i=0;i<5;i++)
	{
		vis[ret.point[i]]++;
		if(vis[ret.point[i]]>maxsame)maxsame=vis[ret.point[i]],maxi=ret.point[i];
	}
	for(i=1;i<=14;i++)
	{
		if(maxi!=i&&vis[i]>secsame)secsame=vis[i];
	}
	if(samec&&isstr)ret.flag=2;//同花顺
	else if(maxsame==4)ret.flag=3;//四条
	else if(maxsame==3&&secsame==2)ret.flag=4;//葫芦
	else if(samec)ret.flag=5;//同花
	else if(isstr)ret.flag=6;//顺子
	else if(maxsame==3)ret.flag=7;//三条
	else if(maxsame==2&&secsame==2)ret.flag=8;//两对
	else if(maxsame==2)ret.flag=9;//一对
	else ret.flag=10;//高牌
	return ret;
}

int biger(Maxcard a,Maxcard b)
{
	if(a.flag<b.flag)return 1;
	else if(a.flag>b.flag)return -1;
	else
	{
		for(int i=0;i<5;i++)
		{
			if(a.point[i]>b.point[i])return 1;
			else if(a.point[i]<b.point[i])return -1;
		}
		return 0;
	}
}

void solve()
{
	Card temp[7];
	Card select[5];
	int i,j,k,l,cnt;
	for(i=2;i<7;i++)temp[i]=Ccard[i-2];
	for(i=0;i<n;i++)//计算每位玩家最大的牌
	{
		temp[0]=Pcard[i][0];
		temp[1]=Pcard[i][1];
		for(j=0;j<6;j++)//枚举第一张不要的牌
		{
			for(k=j+1;k<7;k++)//枚举第二张不要的牌
			{
				cnt=0;
				for(l=0;l<7;l++)
				{
					if(l!=j&&l!=k)select[cnt++]=temp[l];
				}
				Maxcard tt=gettype(select);
				if(biger(tt,maxcard[i])==1)maxcard[i]=tt;
			}
		}
	}
	cnt=1;
	int ansi[N];
	Maxcard ans=maxcard[0];
	ansi[0]=0;
	for(i=1;i<n;i++)
	{
		if(biger(maxcard[i],ans)==1)
		{
			cnt=0;
			ans=maxcard[i];
			ansi[cnt++]=i;
		}
		else if(biger(maxcard[i],ans)==0)
		{
			ansi[cnt++]=i;
		}
	}
	printf("%d\n",cnt);
	printf("%d",ansi[0]+1);
	for(i=1;i<cnt;i++)printf(" %d",ansi[i]+1);
	printf("\n");
}

int main()
{
	while(scanf("%d",&n)!=EOF)
	{
		init();
		int i;
		char p[5],c[5];
		for(i=0;i<n;i++)
		{
			scanf("%s%s",p,c);
			Pcard[i][0].point=getp(p);
			Pcard[i][0].color=c[0];
			scanf("%s%s",p,c);
			Pcard[i][1].point=getp(p);
			Pcard[i][1].color=c[0];
		}
		for(i=0;i<5;i++)
		{
			scanf("%s%s",p,c);
			Ccard[i].point=getp(p);
			Ccard[i].color=c[0];
		}
		solve();
	}
	return 0;
}

/*
2
8 S 4 D
7 C 8 C
8 H K C 5 C A C Q H
6
A H Q C
6 C 4 C
J H 9 C
5 D 3 C
9 D 6 D
3 S J D
7 C 7 S 2 S 10 D J S
6
A D 4 D
4 S 8 D
J D 10 D
6 C 2 H
K D 9 D
6 H 5 H
7 D J C 10 S 3 H 5 S
*/
