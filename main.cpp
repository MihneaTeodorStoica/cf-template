#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;

#if 0
#define int ll
#define uint ull
#endif

/**
 * Problem: ${title}
 * URL: ${url}
 * TL: ${timeLimit} ms
 * ML: ${memoryLimit} MB
 *
 * Good Luck!
*/

void tc() {

}

#define MTC 1
#define FIO 0
#define FN ""

signed main() {
#if FIO == 1 && !defined(LOCAL)
    (void)freopen(FN ".in", "r", stdin);
    (void)freopen(FN ".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#if MTC == 1
    signed tt; cin >> tt;
    while (tt --) tc();
#else
    tc();
#endif
    return 0;
}
