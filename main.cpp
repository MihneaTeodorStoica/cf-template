#include <bits/stdc++.h>
using namespace std;

/**
 * Problem: ${title}
 * URL: ${url}
 * TL: ${timeLimit}
 * ML: ${memoryLimit}
 */
#define MULTITEST 1
#define int long long
inline void tc() {
}

#define FILEIO 0
#define FILE ""
int main() {
#if FILEIO && !defined(LOCAL)
    freopen(FILE ".in", "r", stdin);
    freopen(FILE ".out", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#if MULTITEST == 1
    int tt;
    cin >> tt;
    while (tt--) {
        tc();
    }
#else
    tc();
#endif
    return 0;
}