// rope 的底层是平衡树。支持以下操作：

// | 函数 | 功能 |
// | -- -- -- -- -- -- -- | -- -- -- -- -- -- -- -- |
// | push_back(x) | 在末尾添加x |
// | insert(pos, x) | 在pos插入x |
// | erase(pos, x) | 从pos开始删除x个 |
// | replace(pos, x) | 从pos开始换成x |
// | substr(pos, x) | 提取pos开始x个 |
// | at(x) / [x] | 访问第x个元素 |

// 上述的 pos 是光标，插入 x 指在 pos 前插入。故 pos 的范围在 $[0, rope.size] $​​​。rope 下标从 0 开始。

// tree 的底层也是平衡树。

// 需要引入头文件和命名空间：

#include <ext/rope>
using namespace __gnu_cxx;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// 以一道题为例：

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
using i64 = long long;
using pii = pair<int, int>;

tree<pii, null_type, less<pii>, rb_tree_tag, tree_order_statistics_node_update> t;  //会去重的红黑树

signed main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        t.insert({x, i});
    }
    for (int i = n; i < n + m; i++) {
        int op, x;
        cin >> op >> x;
        if (op == 1)
            t.insert({x, i});  //插入x，用独特的<x,i>标注
        if (op == 2)
            t.erase(t.lower_bound({x, 0}));  //删除x（删除单个元素）
        if (op == 3)
            cout << t.order_of_key({x, 0}) + 1 << endl;  // x的排名（order_of_key = 小于x的元素个数，然后+1）
        if (op == 4)
            cout << t.find_by_order(x - 1)->first << endl;  //排名为x的元素（第x小）
        if (op == 5)
            cout << prev(t.lower_bound({x, 0}))->first << endl;  // x的前驱（小于x且最大）
        if (op == 6)
            cout << t.lower_bound({x + 1, 0})->first << endl;  // x的后继（大于x且最小）
    }
    return 0;
}

// 可持久化应用

// rope 数据间拷贝仅拷贝根节点，所以是 $O(1) $​ 的。只需要调用下面的开辟空间命令就可实现可持久化：

rope<char>*a, *b;
a = new rope<char>;
b = new rope<char>(*a);  // O(1)拷贝

// 实测使用 tree 来可持久化比 rope 慢不少。对于按权值排序的平衡树，使用 rope 时维护一个有序数列即可。