#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
struct Chairman_Tree {  //指针型线段树
    struct node {
        int v, ls, rs;  //当前节点对应的值域包含的值的个数v
    };
    vector<node> e;
    int n, cnt;
    vector<int> T;  //第i个版本对应的线段树的根节点T[i]
    Chairman_Tree(int n)
        : n(n) {
        cnt = 0;
        e.resize(n << 5);
        T.resize(n + 5);
    }
#define v(p) e[p].v
#define ls(p) e[p].ls
#define rs(p) e[p].rs
#define mid (l + r >> 1)
    int update(int pre, int l, int r, int x) {  //令T[i] = update
        int p = ++cnt;
        e[p] = e[pre], v(p)++;
        if (l < r) {
            if (x <= mid)
                ls(p) = update(ls(pre), l, mid, x);
            else
                rs(p) = update(rs(pre), mid + 1, r, x);
        }
        return p;
    }
    int query(int s1, int s2, int l, int r, int cl, int cr) {  //查区间[x,y]对应的版本号s1,s2中值域在[cl,cr]里的值的个数
        if (cl <= l && r <= cr) {
            return v(s2) - v(s1);
        }
        int res = 0;
        if (cl <= mid)
            res = query(ls(s1), ls(s2), l, mid, cl, cr);
        if (cr > mid)
            res += query(rs(s1), rs(s2), mid + 1, r, cl, cr);
        return res;
    }
    int query(int s1, int s2, int l, int r, int k) {  //查区间[x,y]对应的版本号s1,s2中第k小的值。从第1小开始算
        if (l >= r)
            return l;                   //返回第k小的下标
        int x = v(ls(s2)) - v(ls(s1));  //左区间有多少个小于等于mid的值
        if (k <= x)
            return query(ls(s1), ls(s2), l, mid, k);
        else
            return query(rs(s1), rs(s2), mid + 1, r, k - x);
    }
};