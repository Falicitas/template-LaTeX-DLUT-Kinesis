#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 1e6 + 5, inf = 0x7f3f3f3f;

// 吉司机线段树
// 支持 5 个操作：
// 1. 区间加减
// 2. 区间取最值 A = min(A, v)
// 3. 询问区间和
// 4. 询问区间最值
// 5. 询问历史区间最值
// 将区间的 A 值分为最大值和非最大值两部分去维护（再维护最大值的个数 cnt，严格次大值 se）
// 对于区间来说，将操作 2 的 v 值分为 >= mx, >= se, < se 的三个情况去考虑
// 对于 < se，往子节点迭代至符合前两种情况，这么可以将操作 2 变成对于 mx 的区间加减
// 线段树有 log 层，每层的值域原定是 O(n)，则迭代的过程中会使路径上的节点值域个数 -1
// 如果没有区间加减操作，那么复杂度为 O((n + m) logn)
// 对于区间操作，分别对最大值和非最大值进行维护
// 有了这个操作，对于全局，每次会增加至多 log^2 个值域
// 所以总复杂度为 O(n log^2 n)
// 对于历史区间最值，维护历史增减最大的 tag 就行
// tagA, tagAA, tagB, tagBB 分别是最大值tag，历史最大值tag，次大值tag，历史次大值tag

int mx[N << 2], lmx[N << 2], tagA[N << 2], tagAA[N << 2], tagB[N << 2], tagBB[N << 2], cnt[N << 2], len[N << 2], se[N << 2];
i64 sum[N << 2], A[N];
#define lp (p << 1)
#define rp (p << 1 | 1)
#define mid ((l + r) / 2)
#define ls lp, l, mid
#define rs rp, mid + 1, r
void up(int p) {
    mx[p] = max(mx[lp], mx[rp]);
    lmx[p] = max(lmx[lp], lmx[rp]);
    sum[p] = sum[lp] + sum[rp];
    if (mx[lp] > mx[rp]) {
        cnt[p] = cnt[lp];
        se[p] = max(se[lp], mx[rp]);
    } else if (mx[rp] > mx[lp]) {
        cnt[p] = cnt[rp];
        se[p] = max(se[rp], mx[lp]);
    } else {
        cnt[p] = cnt[lp] + cnt[rp];
        se[p] = max(se[lp], se[rp]);
    }
}

void Upd(int p, int k1, int k2, int k3, int k4) {
    sum[p] += 1ll * cnt[p] * k1 + 1ll * (len[p] - cnt[p]) * k3;
    lmx[p] = max(lmx[p], mx[p] + k2);
    tagAA[p] = max(tagAA[p], tagA[p] + k2);
    tagBB[p] = max(tagBB[p], tagB[p] + k4);
    mx[p] += k1;
    tagA[p] += k1;
    tagB[p] += k3;
    if (se[p] != -inf)
        se[p] += k3;
}

void down(int p) {
    int mmx = max(mx[lp], mx[rp]);
    if (mx[lp] == mmx) {
        Upd(lp, tagA[p], tagAA[p], tagB[p], tagBB[p]);
    } else {
        Upd(lp, tagB[p], tagBB[p], tagB[p], tagBB[p]);
    }
    if (mx[rp] == mmx) {
        Upd(rp, tagA[p], tagAA[p], tagB[p], tagBB[p]);
    } else {
        Upd(rp, tagB[p], tagBB[p], tagB[p], tagBB[p]);
    }
    tagA[p] = tagAA[p] = tagB[p] = tagBB[p] = 0;
}

void OP1(int p, int l, int r, int cl, int cr, int k) {
    if (r < cl || l > cr)
        return;
    if (cl <= l && r <= cr) {
        Upd(p, k, k, k, k);
        return;
    }
    down(p);
    OP1(ls, cl, cr, k), OP1(rs, cl, cr, k);
    up(p);
}

i64 Q1(int p, int l, int r, int cl, int cr) {
    if (r < cl || cr < l)
        return 0;
    if (cl <= l && r <= cr) {
        return sum[p];
    }
    down(p);
    return Q1(ls, cl, cr) + Q1(rs, cl, cr);
}

i64 Q2(int p, int l, int r, int cl, int cr) {
    if (r < cl || cr < l)
        return -inf;
    if (cl <= l && r <= cr) {
        return mx[p];
    }
    down(p);
    return max(Q2(ls, cl, cr), Q2(rs, cl, cr));
}

i64 Q3(int p, int l, int r, int cl, int cr) {
    if (r < cl || cr < l)
        return -inf;
    if (cl <= l && r <= cr) {
        return lmx[p];
    }
    down(p);
    return max(Q3(ls, cl, cr), Q3(rs, cl, cr));
}

void update_min(int p, int l, int r, int cl, int cr, int v) {
    if (r < cl || cr < l || mx[p] <= v) {
        return;
    }
    if (cl <= l && r <= cr && se[p] <= v) {
        Upd(p, v - mx[p], v - mx[p], 0, 0);
        return;
    }
    down(p);
    update_min(ls, cl, cr, v), update_min(rs, cl, cr, v);
    up(p);
}

void bld(int p, int l, int r) {
    len[p] = r - l + 1;
    if (l == r) {
        cnt[p] = 1;
        mx[p] = A[l];
        lmx[p] = A[l];
        sum[p] = A[l];
        se[p] = -inf;
        return;
    }
    bld(ls), bld(rs);
    up(p);
};

void run() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    bld(1, 1, n);
    while (m--) {
        int op, l, r, k;
        cin >> op >> l >> r;
        if (op == 1) {
            cin >> k;
            OP1(1, 1, n, l, r, k);
        } else if (op == 2) {
            cin >> k;
            update_min(1, 1, n, l, r, k);
        } else if (op == 3) {
            cout << Q1(1, 1, n, l, r) << "\n";
        } else if (op == 4) {
            cout << Q2(1, 1, n, l, r) << "\n";
        } else {
            cout << Q3(1, 1, n, l, r) << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--) {
        run();
    }
    return 0;
}