#include<stdio.h>
#include<string.h>
#include<algorithm>
#define N 100010
using namespace std;
typedef long long LL;
int a[N];       //原数组
int sorted[N];  //排序好的数组
//是一棵树，但把同一层的放在一个数组里。
int num[20][N];   //num[i] 表示i前面有多少个点进入左孩子
int val[20][N];   //20层,每一层元素排放，0层就是原数组
void build(int l,int r,int ceng)
{
  if(l==r) return ;
  int mid=(l+r)/2,isame=mid-l+1;  //isame保存有多少和sorted[mid]一样大的数进入左孩子
  for(int i=l;i<=r;i++) if(val[ceng][i]<sorted[mid]) isame--;
  int ln=l,rn=mid+1;   //本结点两个孩子结点的开头，ln左
  for(int i=l;i<=r;i++)
  {
    if(i==l) num[ceng][i]=0;
    else num[ceng][i]=num[ceng][i-1];
    if(val[ceng][i]<sorted[mid] || val[ceng][i]==sorted[mid]&&isame>0)
    {
      val[ceng+1][ln++]=val[ceng][i];
      num[ceng][i]++;
      if(val[ceng][i]==sorted[mid]) isame--;
    }
    else
    {
      val[ceng+1][rn++]=val[ceng][i];
}
  }
  build(l,mid,ceng+1);
  build(mid+1,r,ceng+1);
}


int look(int ceng,int sl,int sr,int l,int r,int k)
{
  if(sl==sr) return val[ceng][sl];
  int ly;  //ly 表示l 前面有多少元素进入左孩子
  if(l==sl) ly=0;  //和左端点重合时
  else ly=num[ceng][l-1];
  int tolef=num[ceng][r]-ly;  //这一层l到r之间进入左子树的有tolef个
  if(tolef>=k)
  {
    return look(ceng+1,sl,(sl+sr)/2,sl+ly,sl+num[ceng][r]-1,k);
  }
  else
  {
    // l-sl 表示l前面有多少数，再减ly 表示这些数中去右子树的有多少个
    int lr = (sl+sr)/2 + 1 + (l-sl-ly);  //l-r 去右边的开头位置
    // r-l+1 表示l到r有多少数，减去去左边的，剩下是去右边的，去右边1个，下标就是lr，所以减1
    return look(ceng+1,(sl+sr)/2+1,sr,lr,lr+r-l+1-tolef-1,k-tolef);
  }
}

int main()
{
  int n,m,l,r,k;
  while(scanf("%d%d",&n,&m)!=EOF)
  {

    for(int i=1;i<=n;i++)
    {
      scanf("%d",&val[0][i]);
      sorted[i]=val[0][i];
    }
    sort(sorted+1,sorted+n+1);
    build(1,n,0);
    while(m--)
    {
      scanf("%d%d%d",&l,&r,&k);
      printf("%d\n",look(0,1,n,l,r,k));
    }
  }
  return 0;
}
