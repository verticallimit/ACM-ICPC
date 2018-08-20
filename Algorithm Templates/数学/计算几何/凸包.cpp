/*
求凸包，Graham算法
点的编号0~n-1
返回凸包结果Stack[0~top-1]为凸包的编号
*/
const int maxn = 1010;
Point list[maxn];
int Stack[maxn], top;
//相对于list[0]的极角排序
bool _cmp(Point p1, Point P2) {
    double tmp = (p1 - list[0]) ^ (p2 - list[0]);
    if (sgn(tmp) > 0) return true;
    else if (sgn(tmp) == 0 && sgn(dist(p1, list[0]) - dist(p2, list[0])) <= 0)
        return true;
    else return false;
}
void Graham(int n) {
    Point p0;
    int k = 0;
    p0 = list[0];
    //找最下边的一个点
    for (int i = 1; i < n; i ++) {
        if ((p0.y > list[i].y) || (p0.y == list[i].y && p0.x > list[i].x)) {
            p0 = list[i];
            k = i;
        }
    }
    swap(list[k], list[0]);
    sort(list+1, list+n, _cmp);
    if (n == 1) {
        top = 1;
        Stack[0] = 0;
        return;
    }
    if (n == 2) {
        top = 2;
        Stack[0] = 0;
        Stack[1] = 1;
        return;
    }
    Stack[0] = 0;
    Stack[1] = 1;
    top = 2;
    for (int i = 2; i < n; i++) {
        while (top > 1 && sgn((list[Stack[top-1]] - list[Stack[top-2]])^(list[i]-list[Stack[top-2]])) <= 0)
            top--;
        Stack[top++] = i;
    }
}
