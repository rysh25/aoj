#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <utility>
#include <string>
#include <bitset>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <climits>
#include <cstring>
// #include <cstdlib>
#include <limits>
#include <algorithm>
#include <functional>
#include <vector>
#include <stack>
#include <tuple>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i < (int)(n); i++)
using ll = long long;

int main()
{
    int n, q;
    cin >> n >> q;

    int len = 1;
    while (len < n)
    {
        len <<= 1;
    }

    // cerr << "n=" << n << ", len=" << len << endl;

    vector<int> seg(len * 2, 0);

    auto cerr_seg = [&]()
    {
        cerr << "seg: ";
        int j = 1;
        int cols = 0;
        rep(i, len * 2)
        {
            cerr << seg[i] << " ";
            cols++;
            if (cols == j)
            {
                cerr << " ";
                j <<= 1;
                cols = 0;
            }
        }
        cerr << endl;
    };

    // cerr_seg();

    auto add = [&](int i, int v)
    {
        // cerr << "add: i=" << i << ", v=" << v << endl;
        i += len - 1;
        seg[i] += v;

        while (i > 0)
        {
            i = (i - 1) / 2;
            // cerr << "i=" << i << endl;
            seg[i] = seg[i * 2 + 1] + seg[i * 2 + 2];
        }
    };

    auto get_sum = [&](auto f, int a, int b, int i = 0, int l = 0, int r = -1) -> int
    {
        if (r < 0)
            r = len;

        // cerr << "get_sum: a=" << a << ", b=" << b << ", i=" << i << ", l=" << l << ", r=" << r << endl;

        if (r <= a || b <= l)
            return 0;

        if (a <= l && r <= b)
            return seg[i];

        int m = l + (r - l) / 2;

        return f(f, a, b, i * 2 + 1, l, m) + f(f, a, b, i * 2 + 2, m, r);
    };

    while (q--)
    {
        int com, x, y;
        cin >> com >> x >> y;

        if (com == 0)
        {
            add(x - 1, y);

            // cerr_seg();
        }
        else
        {
            cout << get_sum(get_sum, x - 1, y) << endl;
        }
    }

    return 0;
}
