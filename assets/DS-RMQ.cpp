#include <bits/stdc++.h>
using namespace std;

struct RMQ {
    int n;
    vector<int> lg2;
    vector<vector<int>> dmax, dmin;
    RMQ(const vector<int>& A) {
        n = A.size();
        lg2 = vector<int>(n + 1);
        for (int i = 0; i <= n; i++) {
            lg2[i] = (i == 0 ? -1 : lg2[i >> 1] + 1);
        }
        dmax = vector<vector<int>>(lg2[n] + 1, vector<int>(n));
        dmin = dmax;
        /*以上是数组的初始化*/
        for (int i = 0; i < n; i++)
            dmin[0][i] = dmax[0][i] = A[i];
        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) - 1 < n; i++) {
                dmin[j][i] = min(dmin[j - 1][i], dmin[j - 1][i + (1 << (j - 1))]);
                dmax[j][i] = max(dmax[j - 1][i], dmax[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int query(int l, int r, bool op) {
        int k = lg2[r - l + 1];
        r = r - (1 << k) + 1;
        return op == 0 ? min(dmin[k][l], dmin[k][r]) : max(dmax[k][l], dmax[k][r]);
    }
    /*op为0 min，op为1 max*/
};

struct RMQ_2D {
    int n, m;
    vector<int> lg2;
    vector<vector<vector<vector<int>>>> f;
    RMQ_2D(const vector<vector<int>>& val) {
        n = val.size(), m = val[0].size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                f[0][0][i][j] = val[i][j];
            }
        }
        lg2 = vector<int>(max(n, m) + 1);
        for (int i = 0; i <= max(n, m); i++) {
            lg2[i] = (i == 0 ? -1 : lg2[i >> 1] + 1);
        }
        f = vector(lg2[n] + 1, vector(lg2[m] + 1, vector(n, vector<int>(m))));  // C++17标准
        /*以上是数组的初始化*/
        for (int i = 0; i < n; i++) {
            for (int k2 = 1; (1 << k2) <= m; k2++) {
                for (int j = 0; j + (1 << k2) - 1 < m; j++) {
                    f[0][k2][i][j] = max(f[0][k2 - 1][i][j], f[0][k2 - 1][i][j + (1 << (k2 - 1))]);
                }
            }
        }
        for (int k1 = 1; (1 << k1) <= n; k1++) {
            for (int i = 0; i + (1 << k1) - 1 < n; i++) {
                for (int k2 = 0; (1 << k2) <= m; k2++) {
                    for (int j = 0; j + (1 << k2) - 1 < m; j++) {
                        f[k1][k2][i][j] = max(f[k1 - 1][k2][i][j], f[k1 - 1][k2][i + (1 << (k1 - 1))][j]);
                    }
                }
            }
        }
    }
    int Query(int x1, int x2, int y1, int y2) {
        int k1 = lg2[x2 - x1 + 1], k2 = lg2[y2 - y1 + 1];
        x2 = x2 - (1 << k1) + 1, y2 = y2 - (1 << k2) + 1;
        return max(max(f[k1][k2][x1][y1], f[k1][k2][x2][y1]), max(f[k1][k2][x1][y2], f[k1][k2][x2][y2]));
    }
};