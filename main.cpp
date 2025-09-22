/*
    __  ___          __        __             __  ____ __                    ______               __           _____ __        _           
   /  |/  /___ _____/ /__     / /_  __  __   /  |/  (_) /_  ____  ___  ____ /_  __/__  ____  ____/ /___  _____/ ___// /_____  (_)________ _
  / /|_/ / __ `/ __  / _ \   / __ \/ / / /  / /|_/ / / __ \/ __ \/ _ \/ __ `// / / _ \/ __ \/ __  / __ \/ ___/\__ \/ __/ __ \/ / ___/ __ `/
 / /  / / /_/ / /_/ /  __/  / /_/ / /_/ /  / /  / / / / / / / / /  __/ /_/ // / /  __/ /_/ / /_/ / /_/ / /   ___/ / /_/ /_/ / / /__/ /_/ / 
/_/  /_/\__,_/\__,_/\___/  /_.___/\__, /  /_/  /_/_/_/ /_/_/ /_/\___/\__,_//_/  \___/\____/\__,_/\____/_/   /____/\__/\____/_/\___/\__,_/  
                                 /____/                                                                                                    
*/

#include <bits/stdc++.h>
using namespace std;

// ============================ toggles ============================
#define MULTIPLE_TESTCASES 1   // 1 => read T; 0 => single test
#define DEFINE_INT_LL      1   // 1 => #define int long long
#define DEBUG              0   // 1 => enable DBG/DUMP/ASSERT + Timer
#define FASTIO             1
#define FILEIO             0
#define FILENAME           ""  // used only if FILEIO==1

// ============================ base types =========================
#if DEFINE_INT_LL
#  define int long long
#  define uint unsigned long long
#else
using uint = unsigned int;
#endif
using ll = long long; using ull = unsigned long long; using ld = long double;

// ============================== debug ============================
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

// ============================== micro-profiler ===================
#if DEBUG
struct Timer {
    std::chrono::steady_clock::time_point t = std::chrono::steady_clock::now();
    ~Timer(){
        auto d = std::chrono::steady_clock::now() - t;
        std::cerr << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(d).count() << " ms\n";
    }
} _timer_guard;
#endif

// ============================== helpers ==========================
// Y-combinator (recursive lambdas)
template<class F> struct Fix : F { using F::F; template<class... A> decltype(auto) operator()(A&&... a) const { return F::operator()(*this, std::forward<A>(a)...); } };
template<class F> Fix(F) -> Fix<F>;

// __int128 printing
using i128 = __int128_t; using u128 = __uint128_t;
inline std::ostream& operator<<(std::ostream& os, i128 v){
    if(v < 0){ os << '-'; v = -v; }
    char s[40]; int n=0; do{ s[n++] = char('0' + (int)(v % 10)); v /= 10; }while(v);
    while(n--) { os << s[n]; } return os;
}

// math helpers
template<class T> inline bool chmin(T& a, const T& b){ if(b < a){ a = b; return true; } return false; }
template<class T> inline bool chmax(T& a, const T& b){ if(b > a){ a = b; return true; } return false; }
// For a>=0, b>0
template<class T> constexpr T ceil_div_pos(T a, T b){ return (a + b - 1) / b; }
template<class T> constexpr T floor_div_pos(T a, T b){ return a / b; }

// grid directions
constexpr int dx4[4] = {-1, 1, 0, 0};
constexpr int dy4[4] = { 0, 0,-1, 1};
constexpr int dx8[8] = {-1,-1,-1, 0,0, 1, 1, 1};
constexpr int dy8[8] = {-1, 0, 1,-1,1,-1, 0, 1};

// vector I/O
template<class T> inline void read_vec(std::vector<T>& a, int n){ a.resize(n); for(int i=0;i<n;++i) cin >> a[i]; }
template<class T> inline void print_vec(const std::vector<T>& a, char sep=' ', char end='\n'){
    for(int i=0;i<(int)a.size();++i){ if(i) cout << sep; cout << a[i]; } cout << end;
}

// pair hash (generic)
inline void hash_combine(std::size_t& seed, std::size_t v){ seed ^= v + 0x9e3779b97f4a7c15ULL + (seed<<6) + (seed>>2); }
struct PairHash {
    template<class A, class B>
    size_t operator()(const std::pair<A,B>& p) const noexcept {
        size_t h=0; hash_combine(h, std::hash<A>{}(p.first)); hash_combine(h, std::hash<B>{}(p.second)); return h;
    }
};

// ============================ problem glue =======================
/**
 * Problem: ${title}
 * URL:     ${url}
 * TL:      ${timeLimit} ms
 * 
 * Good Luck!
 */
signed TC = 1, TT = 1;

inline void tc(){

}

signed main(){
#if FASTIO
    ios::sync_with_stdio(false); cin.tie(nullptr);
#endif
#if FILEIO
    freopen(FILENAME ".in", "r", stdin);
    freopen(FILENAME ".out", "w", stdout);
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
