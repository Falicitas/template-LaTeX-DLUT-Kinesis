namespace bit {
i64 c[M];
inline int lowbit(int x) {
    return x & -x;
}
void add(int x, i64 v) {
    for (; x < M; x += lowbit(x))
        c[x] += v;
}
i64 sum(int x) {
    i64 ret = 0;
    for (; x > 0; x -= lowbit(x))
        ret += c[x];
    return ret;
}
int kpos(i64 k) {  //找到前缀第一个>=k的pos
    int p = 0;
    for (int lim = 1 << 20; lim; lim /= 2)
        if (p + lim < M && c[p + lim] < k) {
            p += lim;
            k -= c[p];
        }
    return p + 1;
}
}  // namespace bit