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
#pragma GCC target("sse4.2,avx2,bmi2,fma,popcnt,arch=skylake,tune=native")
using namespace std;

// ============================ toggles ============================
#define MULTIPLE_TESTCASES 1
#define DEFINE_INT_LL      1
#define DEBUG              0
#define FASTIO             1
#define FILEIO             0
#define FILENAME           ""

// feature toggles
#define USE_RNG            1

// ============================ base types =========================
#if DEFINE_INT_LL
#  define int long long
using uint = unsigned long long;
#else
using uint = unsigned int;
#endif
using ll = long long; using ull = unsigned long long; using ld = long double;

// ============================== debug ============================
// Zero-overhead when DEBUG==0. Pretty-prints scalars, pairs, tuples, ranges.
#if DEBUG
namespace dbg {
    using std::cerr; using std::string; using std::string_view;

    template<class T, class = void> struct is_iterable : std::false_type {};
    template<class T> struct is_iterable<T, std::void_t<decltype(begin(std::declval<T>())), decltype(end(std::declval<T>()))>> : std::true_type {};
    template<class T> inline constexpr bool is_stringlike =
        std::is_same_v<std::decay_t<T>, string> || std::is_same_v<std::decay_t<T>, string_view> || std::is_same_v<std::decay_t<T>, const char*>;

    inline void _print(const string& s){ cerr<<s; } inline void _print(string_view s){ cerr<<s; }
    inline void _print(const char* s){ cerr<<s; } inline void _print(char c){ cerr<<c; }
    inline void _print(bool b){ cerr<<(b?"true":"false"); }
    template<class T> std::enable_if_t<!is_iterable<T>::value && !is_stringlike<T>> _print(const T& x){ cerr<<x; }

    template<class A, class B> void _print(const pair<A,B>& p){ cerr<<'(' ; _print(p.first); cerr<<','; _print(p.second); cerr<<')'; }
    template<class... Ts> void _print(const tuple<Ts...>& t){
        cerr<<'(';
        size_t k=0; std::apply([&](auto const&... xs){ ((k++?cerr<<',' : cerr, _print(xs)), ...); }, t);
        cerr<<')';
    }
    template<class T> std::enable_if_t<is_iterable<T>::value && !is_stringlike<T>> _print(const T& a){
        cerr<<'['; bool f=true; for (auto const& v: a){ if(!f) cerr<<','; f=false; _print(v);} cerr<<']';
    }

    inline void _split_names(string_view s, vector<string_view>& out){
        size_t i=0, n=s.size(), par=0, brk=0, ang=0;
        auto flush=[&](size_t l,size_t r){ while(l<r && s[l]==' ') ++l; while(r>l && s[r-1]==' ') --r; if(l<r) out.emplace_back(s.substr(l,r-l)); };
        for(size_t j=0;j<n;++j){ char c=s[j];
            par += (c=='(') - (c==')'); brk += (c=='[') - (c==']'); ang += (c=='<') - (c=='>');
            if(c==',' && !par && !brk && !ang){ flush(i,j); i=j+1; }
        } flush(i,n);
    }
    template<class... Args> void vars(string_view names, const Args&... args){
        vector<string_view> v; v.reserve(sizeof...(Args)); _split_names(names, v); size_t i=0;
        auto one=[&](auto const& val){ if(i<v.size()) { cerr<<v[i]<<'='; } _print(val); if(++i<v.size()) cerr<<" | "; };
        (one(args), ...); cerr<<'\n';
    }
}
#  define DBG(...) do{ std::cerr<<"[L"<<__LINE__<<"] "; dbg::vars(#__VA_ARGS__, __VA_ARGS__); }while(0)
#  define DUMP(expr) do{ std::cerr<<"[L"<<__LINE__<<"] "<<#expr<<'='; dbg::_print((expr)); std::cerr<<'\n'; }while(0)
#  define ASSERT(x) do{ if(!(x)){ std::cerr<<"ASSERT FAIL @L"<<__LINE__<<": " #x "\n"; std::abort(); } }while(0)
#else
#  define DBG(...)   do{}while(0)
#  define DUMP(x)    do{}while(0)
#  define ASSERT(x)  do{ (void)sizeof(x); }while(0)
#endif

// ============================== rng ==============================
#if USE_RNG
static uint64_t splitmix64(uint64_t x){ x+=0x9e3779b97f4a7c15ULL; x=(x^(x>>30))*0xbf58476d1ce4e5b9ULL; x=(x^(x>>27))*0x94d049bb133111ebULL; return x^(x>>31); }
struct FastRNG{
    uint64_t s; FastRNG(): s(chrono::high_resolution_clock::now().time_since_epoch().count()) {}
    uint64_t operator()(){ return s = splitmix64(s); }
    uint64_t operator()(uint64_t lim){ return operator()()%lim; }
    template<class It> void shuffle(It l, It r){ for(auto n=r-l; n>1; --n){ auto j=(*this)(n); iter_swap(l+(n-1), l+j); } }
} rng;
#endif

// ============================ problem glue =======================
/**
 * Problem: ${title}
 * URL:    ${url}
 * TL:     ${timeLimit} ms
 */
signed TC = 1, TT = 1;

inline void tc() {
    
}

signed main(){
#if FASTIO
    ios::sync_with_stdio(false); cin.tie(nullptr);
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
#else
    TT = 1;
#endif

    for (; TC <= TT; ++TC){
#if DEBUG
        cerr << "Testcase#" << TC << '\n';
#endif
        tc();
    }
    return 0;
}
