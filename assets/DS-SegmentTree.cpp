#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 1e6 + 5, inf = 0x3f3f3f3f;

int mx[N << 2], tag[N << 2], tag2[N << 2];  // tag区间加减，tag2区间

#define lp (p << 1)
#define rp (p << 1 | 1)
#define mid ((l + r) / 2)
#define ls lp, l, mid
#define rs rp, mid + 1, r
void up(int p) {
    mx[p] = max(mx[lp], mx[rp]);
}

void Add(int p, int v) {
    mx[p] += v;
    tag[p] += v;
}

void down(int p) {
    if (tag[p]) {
        Add(lp, tag[p]);
        Add(rp, tag[p]);
        tag[p] = 0;
    }
}

int query(int p, int l, int r, int cl, int cr) {
    if (cl <= l && r <= cr) {
        return mx[p];
    }
    down(p);
    int res = -inf;
    if (cl <= mid)
        res = query(ls, cl, cr);
    if (cr > mid) {
        res = max(res, query(rs, cl, cr));
    }
    return res;
}

void Add(int p, int l, int r, int x, int v) {
    if (l == r) {
        mx[p] += v;
        return;
    }
    down(p);
    if (x <= mid)
        Add(ls, x, v);
    else {
        Add(rs, x, v);
    }
    up(p);
}
