#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 1e6 + 5, inf = 0x7f3f3f3f;

//区间加减，维护区间和、区间max
int mx[N << 2], tag[N << 2], len[N << 2];
i64 sum[N << 2], A[N];
#define lp (p << 1)
#define rp (p << 1 | 1)
#define mid ((l + r) / 2)
#define ls lp, l, mid
#define rs rp, mid + 1, r
void up(int p) {
    mx[p] = max(mx[lp], mx[rp]);
    sum[p] = sum[lp] + sum[rp];
}

void Upd(int p, int v) {
    mx[p] += v;
    sum[p] += 1ll * len[p] * v;
    tag[p] += v;
}

void down(int p) {
    Upd(lp, tag[p]);
    Upd(rp, tag[p]);
    tag[p] = 0;
}

i64 Q1(int p, int l, int r, int cl, int cr) {  //区间和
    if (r < cl || cr < l)
        return 0;
    if (cl <= l && r <= cr) {
        return sum[p];
    }
    down(p);
    return Q1(ls, cl, cr) + Q1(rs, cl, cr);
}

i64 Q2(int p, int l, int r, int cl, int cr) {  //区间max
    if (r < cl || cr < l)
        return -inf;
    if (cl <= l && r <= cr) {
        return mx[p];
    }
    down(p);
    return max(Q2(ls, cl, cr), Q2(rs, cl, cr));
}

void Chg(int p, int l, int r, int cl, int cr, int v) {
    if (r < cl || cr < l) {
        return;
    }
    if (cl <= l && r <= cr) {
        Upd(p, v);
        return;
    }
    down(p);
    Chg(ls, cl, cr, v), Chg(rs, cl, cr, v);
    up(p);
}

void bld(int p, int l, int r) {
    len[p] = r - l + 1;
    if (l == r) {
        mx[p] = A[l];
        sum[p] = A[l];
        return;
    }
    bld(ls), bld(rs);
    up(p);
};
