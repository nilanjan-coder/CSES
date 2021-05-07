//g++ -Wall -Wextra -pedantic -std=c++17 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
//Fast IO: Use scanf and printf
//For printing real values when error <= 10 ^ (-x), do: cout << fixed << setprecision(x + 1) << val << endl;
#include <ext/pb_ds/assoc_container.hpp>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
template<typename T> long long SIZE(T (&t)){ return t.size(); } template<typename T, size_t N> long long SIZE(T (&t)[N]){ return N; } string to_string(char t){ return "'" + string({t}) + "'"; } string to_string(bool t){ return t ? "true" : "false"; } string to_string(const string &t, long long x1=0, long long x2=1e18){ string ret = ""; for(long long i = min(x1,SIZE(t)), _i = min(x2,SIZE(t)-1); i <= _i; ++i){ ret += t[i]; } return '"' + ret + '"'; } string to_string(const char* t){ string ret(t); return to_string(ret); } template<size_t N> string to_string(const bitset<N> &t, long long x1=0, long long x2=1e18){ string ret = ""; for(long long i = min(x1,SIZE(t)); i <= min(x2,SIZE(t)-1); ++i){ ret += t[i] + '0'; } return to_string(ret); } template<typename T, typename... Coords> string to_string(const T (&t), long long x1=0, long long x2=1e18, Coords... C); template<typename T, typename S> string to_string(const pair<T, S> &t){ return "(" + to_string(t.first) + ", " + to_string(t.second) + ")"; } template<typename T, typename... Coords> string to_string(const T (&t), long long x1, long long x2, Coords... C){ string ret = "["; x1 = min(x1, SIZE(t)); auto e = begin(t); advance(e,x1); for(long long i = x1, _i = min(x2,SIZE(t)-1); i <= _i; ++i){ ret += to_string(*e, C...) + (i != _i ? ", " : ""); e = next(e); } return ret + "]"; } template<long long Index, typename... Ts> struct print_tuple{ string operator() (const tuple<Ts...>& t) { string ret = print_tuple<Index - 1, Ts...>{}(t); ret += (Index ? ", " : ""); return ret + to_string(get<Index>(t)); } }; template<typename... Ts> struct print_tuple<0, Ts...> { string operator() (const tuple<Ts...>& t) { return to_string(get<0>(t)); } }; template<typename... Ts> string to_string(const tuple<Ts...>& t) { const auto Size = tuple_size<tuple<Ts...>>::value; return print_tuple<Size - 1, Ts...>{}(t); } void dbgr(){;} template<typename Heads, typename... Tails> void dbgr(Heads H, Tails... T){ cout << to_string(H) << " | "; dbgr(T...); } void dbgs(){;} template<typename Heads, typename... Tails> void dbgs(Heads H, Tails... T){ cout << H << " "; dbgs(T...); } 
#define dbgv(...) cout << to_string(__VA_ARGS__) << endl;
#define dbg(...) cout << "[" << #__VA_ARGS__ << "]: "; dbgv(__VA_ARGS__);
#define dbgr(...) dbgr(__VA_ARGS__); cout << endl;
#define dbgm(...) cout << "[" << #__VA_ARGS__ << "]: "; dbgr(__VA_ARGS__);
using indexed_set = tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update>;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
using ll = long long;
struct segment_tree {
	vector <ll> a;
	int s = 1;
	void init (int n) {
		while (s < n) s *= 2;
		a.assign(2 * s, 0);
	}
	void update (int i, ll v, int x, int lx, int rx) {
		if (rx - lx == 1) {
			a[x] = v;
			return;
		}
		int mx = (lx + rx) / 2;
		if (i < mx) update(i, v, 2 * x + 1, lx, mx);
		else update(i, v, 2 * x + 2, mx, rx);
		a[x] = a[2 * x + 1] + a[2 * x + 2];
	}
	void update (int i, ll v) {
		update(i, v, 0, 0, s);
	}
	ll query (int l, int r, int x, int lx, int rx) {
		if (l >= rx || r <= lx) return 0;
		else if (lx >= l && rx <= r) return a[x];
		else {
			int mx = (lx + rx) / 2;
			return query(l, r, 2 * x + 1, lx, mx) + query(l, r, 2 * x + 2, mx, rx);
		}
	}
	ll query (int l, int r) {
		return query(l, r + 1, 0, 0, s);
	}
};
int main() {
	int n, q;
	cin >> n >> q;
	segment_tree z;
	z.init(n);
	for (int i = 0; i < n; i ++) {
		ll x;
		cin >> x;
		z.update(i, x);
	}
	while (q --) {
		int t;
		cin >> t;
		if (t == 1) {
			int k;
			ll u;
			cin >> k >> u;
			-- k;
			z.update(k, u);
		}
		else {
			int a, b;
			cin >> a >> b;
			-- a; -- b;
			cout << z.query(a, b) << endl;
		}
	}
}