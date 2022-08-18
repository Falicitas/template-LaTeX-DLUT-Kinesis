#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

constexpr int N = 1e6 + 5;

namespace uf {  // undo并查集
int undo[N], top, fa[N], sz[N];
void init() {
    memset(fa, -1, sizeof fa);
    memset(sz, 0, sizeof sz);
    top = 0;
}
int findset(int x) {
    while (fa[x] != -1)
        x = fa[x];
    return x;
}
bool join(int x, int y) {
    x = findset(x);
    y = findset(y);
    if (x == y)
        return false;
    if (sz[x] > sz[y])
        swap(x, y);
    undo[top++] = x;
    fa[x] = y;
    sz[y] += sz[x] + 1;
    return true;
}
inline int checkpoint() {
    return top;
}
void rewind(int t) {
    while (top > t) {
        int x = undo[--top];
        sz[fa[x]] -= sz[x] + 1;
        fa[x] = -1;
    }
}
}  // namespace uf