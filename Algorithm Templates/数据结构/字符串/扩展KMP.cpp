拓展kmp是对KMP算法的扩展，它解决如下问题：

定义母串S，和字串T，设S的长度为n，T的长度为m，求T与S的每一个后缀的最长公共前缀，也就是说，设extend数组,extend[i]表示T与S[i,n-1]的最长公共前缀，要求出所有extend[i](0<=i<n)。

注意到，如果有一个位置extend[i]=m,则表示T在S中出现，而且是在位置i出现，这就是标准的KMP问题，所以说拓展kmp是对KMP算法的扩展，所以一般将它称为扩展KMP算法。

#include <bits/stdc++.h>
using namespace std;

#define next next1

const int maxn=100010;   //字符串长度最大值
int next[maxn],ex[maxn]; //ex数组即为extend数组
//预处理计算next数组
void GETNEXT(char *str)
{
    int i=0,j,po,len=strlen(str);
    next[0]=len;//初始化next[0]
    while(str[i]==str[i+1]&&i+1<len)//计算next[1]
    i++;
    next[1]=i;
    po=1;//初始化po的位置
    for(i=2;i<len;i++)
    {
        if(next[i-po]+i<next[po]+po)//第一种情况，可以直接得到next[i]的值
        next[i]=next[i-po];
        else//第二种情况，要继续匹配才能得到next[i]的值
        {
            j=next[po]+po-i;
            if(j<0)j=0;//如果i>po+next[po],则要从头开始匹配
            while(i+j<len&&str[j]==str[j+i])//计算next[i]
            j++;
            next[i]=j;
            po=i;//更新po的位置
        }
    }
}
//计算extend数组
void EXKMP(char *s1,char *s2)
{
    int i=0,j,po,len=strlen(s1),l2=strlen(s2);
    GETNEXT(s2);//计算子串的next数组
    while(s1[i]==s2[i]&&i<l2&&i<len)//计算ex[0]
    i++;
    ex[0]=i;
    po=0;//初始化po的位置
    for(i=1;i<len;i++)
    {
        if(next[i-po]+i<ex[po]+po)//第一种情况，直接可以得到ex[i]的值
        ex[i]=next[i-po];
        else//第二种情况，要继续匹配才能得到ex[i]的值
        {
            j=ex[po]+po-i;
            if(j<0)j=0;//如果i>ex[po]+po则要从头开始匹配
            while(i+j<len&&j<l2&&s1[j+i]==s2[j])//计算ex[i]
            j++;
            ex[i]=j;
            po=i;//更新po的位置
        }
    }
}

int main() {
    char s[maxn], t[maxn];
    while (scanf("%s%s", t, s) != EOF) {
        memset(next, 0, sizeof(next));
        memset(ex, 0, sizeof(ex));
        EXKMP(s, t);
        int maxx = 0;
        int pos = 0;
        for (int i = 0; i < strlen(s); i++) {
            if (ex[i] != strlen(s) - i) continue;
            if (maxx < ex[i]) {
                maxx = ex[i];
                pos = i;
                break;
            }
        }
        for (int i = pos; i < pos + maxx; i++) {
            printf("%c", s[i]);
        }
        if (maxx == 0) printf("0\n");
        else printf(" %d\n", maxx);
    }

}
