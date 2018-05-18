//适用于正负整数
template <class T>
inline bool scan_d(T &ret) {
   char c; int sgn;
   if(c=getchar(),c==EOF) return 0; //EOF
   while(c!='-'&&(c<'0'||c>'9')) c=getchar();
   sgn=(c=='-')?-1:1;
   ret=(c=='-')?0:(c-'0');
   while(c=getchar(),c>='0'&&c<='9') ret=ret*10+(c-'0');
   ret*=sgn;
   return 1;
}
inline void out(int x) {
   if(x>9) out(x/10);
   putchar(x%10+'0');
}

//strtok和sscanf 结合输入
gets(buf);
int v;
char *p = strrtok(buf, " ");
while (p) {
    sscanf(p, "%d", &v);
    p = strtok(NULL, " ");
}
