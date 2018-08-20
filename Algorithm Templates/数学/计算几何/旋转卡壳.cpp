求解平面最远点对
struct Point {
    int x, y;
    Point(int _x = 0, int _ y = 0) {
        x = _x; y = _y;
    }
    Point operator -(const Point &b)const {
        return Point(x - b.x, y - b.y);
    }
    int operator ^(const Point &b)const {
        return x*b.y - y*b.x;
    }
    int operator *(const Point &b)const {
        return x*b.x + y*b.y;
    }
    void input() {
        scanf("%d%d", &x, &y);
    }
};
//距离的平方
int dist2(Point a, Point b) {
    return (a-b)*(a-b);
}
// 二维凸包，int
const int maxn = 50010;
Point list[maxn];
int Stack[maxn], top;
bool _cmp(Point p1, Point p2) {
    int tmp = (p1 - list[0])^(p2 - list[0]);
    if (tmp > 0) return true;
    else if (tmp == 0 && dist2(p1, list[0]) <= dist2(p2, list[0]))
        return true;
    else return false;
}
void Graham(int n) {
    Point p0;
    int k = 0;
    p0 = list[0];
    for (int i = 1; i < n; i++) {
        
    }

}
