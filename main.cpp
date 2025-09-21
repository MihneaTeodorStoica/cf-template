/*
    __  ___          __        __             __  ____ __                    ______               __           _____ __        _           
   /  |/  /___ _____/ /__     / /_  __  __   /  |/  (_) /_  ____  ___  ____ /_  __/__  ____  ____/ /___  _____/ ___// /_____  (_)________ _
  / /|_/ / __ `/ __  / _ \   / __ \/ / / /  / /|_/ / / __ \/ __ \/ _ \/ __ `// / / _ \/ __ \/ __  / __ \/ ___/\__ \/ __/ __ \/ / ___/ __ `/
 / /  / / /_/ / /_/ /  __/  / /_/ / /_/ /  / /  / / / / / / / / /  __/ /_/ // / /  __/ /_/ / /_/ / /_/ / /   ___/ / /_/ /_/ / / /__/ /_/ / 
/_/  /_/\__,_/\__,_/\___/  /_.___/\__, /  /_/  /_/_/_/ /_/_/ /_/\___/\__,_//_/  \___/\____/\__,_/\____/_/   /____/\__/\____/_/\___/\__,_/  
                                 /____/                                                                                                    
*/
#pragma GCC optimize("Ofast,unroll-loops,inline-functions")
#include <bits/stdc++.h>
#include <bits/extc++.h>
#pragma GCC target("sse4.2,avx2,bmi2,fma,popcnt,arch=skylake,tune=native")
using namespace std;
using namespace __gnu_pbds;
template<typename... Args>void debug(const Args&...);
// ===============================================================
/**
 * Problem name: ${title}
 * URL: ${url}
 * Time Limit: ${timeLimit} ms
 * 
 * Good Luck!
 */
int TC = 1, TT = 1;
inline void tc() {
    
}
#define MULTIPLE_TESTCASES 1
#define DEBUG              0
#define FASTIO             1
#define FILEIO             0
#define FILENAME           ""
// ===============================================================
#if DEBUG
template<typename T> void _print_one(const T& x) { cout << x; }
template<typename T, typename... Args> void _print_one(const T& first, const Args&... rest) { cout << first; _print_one(rest...); }
template<typename... Args> void debug(const Args&... args) { _print_one(args...); cout << "\n"; }
#else
template<typename... Args> void debug(const Args&...) {}
#endif
signed main() {
#if FASTIO
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
#endif
#if FILEIO
    #if FILENAME[0] != '\0'
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
    #else
        #error "FILEIO enabled but FILENAME is empty"
    #endif
#endif
#if MULTIPLE_TESTCASES
    cin >> TT;
#endif
    for (; TC <= TT; TC ++) {
#if DEBUG
        cout << "Testcase #" << TC << ":\n";
#endif
        tc();
    }
    return 0;
}
