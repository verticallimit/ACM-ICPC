1.vector
vector<int> v[10];
v[i].push_back(1);
v[i].size();
2.set/multiset
set<string> s;
s.insert("acm");
set<string>::iterator it;
for (it = country.begin(); it != country.end(); ++it) {
    cout << * it  << " ";
}
s.erase("acm");//删除元素
s.count("acm");//统计个数
s.clear();//清空集合
3.map/multimap
map<string, int> m;
m["acm"] = 2;
m.count("acm");
for (map<string, int>::iterator it = dict.begin(); it != dict.end(); ++it) {
    cout << it->first << " is in class " << it->second << endl;
}
dict.clear();
4.stack
stack<int> S;
S.push(1);
while (!S.empty()) {
    cout << S.top() << endl;
    S.pop();
}
5.queue
queue<int> q;
q.push(1);
while (!q.empty()) {
    cout << q.front() << endl;
    q.pop();
}
6.优先队列
priority_queue<int> q;
priority_queue 模板类有三个模板参数，第一个是元素类型，第二个容器类型，第三个是比较算子。
其中后两个都可以省略，默认容器为vector，默认算子为less，即小的往前排，大的往后排（出队时序列尾的元素出队）。
priority_queue<int> q1;
priority_queue< pair<int, int> > q2; // 注意在两个尖括号之间一定要留空格
rr q3; //定义小的先出队
struct Node{
    int x, y;
    Node(int a = 0, int b= 0):x(a), y(b) {}
};
bool operator < (const Node& a, const Node& b ){
    if (a.x == b.x)
        return a.y > b.y;
    return a.x > b.x;
}
priority_queue<Node> q;

7.make_pair

8.string
string s;
s.empty();
s.size();
s.c_str();//返回char*类型的字符串
s.append("abc");//字符串尾部追加
s = s + "abc";
==,!=,<,<=,>,>=  字符串比较，两个字符串短的与长的前面匹配，短的小于长的
s.substr(i,j);截取s串中从i到j的子串
s.replace(3,3,"good");从第三个起连续三个替换为good
reverse(s.begin(),s.end());  反向排序函数，即字符串反转函数
9.list
list<int> a;
a.push_back(1);
调用resize(n)将list的长度改为只容纳n个元素，超出的元素将被删除。如果n比list原来的长度长，那么默认超出的部分元素置为0。也可以用resize(n, m)的方式将超出的部分赋值为m。
使用list的成员函数push_back和push_front插入一个元素到list中。其中push_back()是从list的末端插入，而push_front()是从list的头部插入。
通过front()可以获得list容器中的头部元素，通过back()可以获得list容器的最后一个元素。
使用pop_back()可以删掉尾部第一个元素，pop_front()可以删掉头部第一个元素。
swap(a,b);//交换两个链表
reverse(b.begin(),b.end());//逆置
a.splice(a.begin(), b);//把b合并到a上
a.merge(b)//merge合并是会自动排序的、调用结束后b变为空，a中元素包含原来a和b的元素。
a.insert(a.begin(),100);  //在a的开始位置（即头部）插入100
a.erase(a.begin());  //将a的第一个元素删除
a.remove(7);//删除a中值为7的元素
10.dequeue
push_front();
push_back();
pop_front();
pop_back();
erase();insert();

11.unique
sort(a,a+n);
n = unique(a,a+n) - a;//关键的一句
