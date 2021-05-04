//g++ -Wall -Wextra -pedantic -std=c++17 -O2 -Wshadow -Wformat=2 -Wfloat-equal -Wconversion -Wlogical-op -Wshift-overflow=2 -Wduplicated-cond -Wcast-qual -Wcast-align -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -fstack-protector
//Fast IO: Use scanf and printf
//For printing real values when error <= 10 ^ (-x), do: cout << fixed << setprecision(x + 1) << val << endl;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
using namespace __gnu_pbds;
using namespace std;
template<typename T> long long SIZE(T (&t)){ return t.size(); } template<typename T, size_t N> long long SIZE(T (&t)[N]){ return N; } string to_string(char t){ return "'" + string({t}) + "'"; } string to_string(bool t){ return t ? "true" : "false"; } string to_string(const string &t, long long x1=0, long long x2=1e18){ string ret = ""; for(long long i = min(x1,SIZE(t)), _i = min(x2,SIZE(t)-1); i <= _i; ++i){ ret += t[i]; } return '"' + ret + '"'; } string to_string(const char* t){ string ret(t); return to_string(ret); } template<size_t N> string to_string(const bitset<N> &t, long long x1=0, long long x2=1e18){ string ret = ""; for(long long i = min(x1,SIZE(t)); i <= min(x2,SIZE(t)-1); ++i){ ret += t[i] + '0'; } return to_string(ret); } template<typename T, typename... Coords> string to_string(const T (&t), long long x1=0, long long x2=1e18, Coords... C); template<typename T, typename S> string to_string(const pair<T, S> &t){ return "(" + to_string(t.first) + ", " + to_string(t.second) + ")"; } template<typename T, typename... Coords> string to_string(const T (&t), long long x1, long long x2, Coords... C){ string ret = "["; x1 = min(x1, SIZE(t)); auto e = begin(t); advance(e,x1); for(long long i = x1, _i = min(x2,SIZE(t)-1); i <= _i; ++i){ ret += to_string(*e, C...) + (i != _i ? ", " : ""); e = next(e); } return ret + "]"; } template<long long Index, typename... Ts> struct print_tuple{ string operator() (const tuple<Ts...>& t) { string ret = print_tuple<Index - 1, Ts...>{}(t); ret += (Index ? ", " : ""); return ret + to_string(get<Index>(t)); } }; template<typename... Ts> struct print_tuple<0, Ts...> { string operator() (const tuple<Ts...>& t) { return to_string(get<0>(t)); } }; template<typename... Ts> string to_string(const tuple<Ts...>& t) { const auto Size = tuple_size<tuple<Ts...>>::value; return print_tuple<Size - 1, Ts...>{}(t); } void dbgr(){;} template<typename Heads, typename... Tails> void dbgr(Heads H, Tails... T){ cout << to_string(H) << " | "; dbgr(T...); } void dbgs(){;} template<typename Heads, typename... Tails> void dbgs(Heads H, Tails... T){ cout << H << " "; dbgs(T...); } 
#define dbgv(...) cout << to_string(__VA_ARGS__) << endl;
#define dbg(...) cout << "[" << #__VA_ARGS__ << "]: "; dbgv(__VA_ARGS__);
#define dbgr(...) dbgr(__VA_ARGS__); cout << endl;
#define dbgm(...) cout << "[" << #__VA_ARGS__ << "]: "; dbgr(__VA_ARGS__);
using ordered_set = tree<pair<int,int>,null_type,less<pair<int,int>>,rb_tree_tag,tree_order_statistics_node_update>;
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
			a[x] += v;
			return;
		}
		int mx = (lx + rx) / 2;
		if (i < mx) update (i, v, 2 * x + 1, lx, mx);
		else update (i, v, 2 * x + 2, mx, rx);
		a[x] = a[2 * x + 1] + a[2 * x + 2];
	}
	void update (int i, ll v) {
		update (i, v, 0, 0, s);
	}
	ll query (int l, int r, int x, int lx, int rx) {
		if (l >= rx || r <= lx) return 0;
		else if (lx >= l && rx <= r) return a[x];
		else {
			int mx = (lx + rx) / 2;
			return query (l, r, 2 * x + 1, lx, mx) + query (l, r, 2 * x + 2, mx, rx);
		}
	}
	ll query (int l, int r) {
		return query (l, r, 0, 0, s);
	}
};
struct tree_trav_arr {
	int n, idx;
	vector <vector <int>> g;
	vector <ll> a, sum, val;
	vector <int> sz, pos;
	segment_tree st;
	void init (int s) {
		n = s;
		g.resize(n);
		a.resize(n);
		sum.resize(n);
		sz.assign(n, 1);
		pos.resize(n);
		st.init(n);
		idx = 0;
	}
	void add_val (int i, ll v) {
		sum[i] = a[i] = v;
	}
	void add_edge (int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void dfs_sum (int u, int p) {
		for (int v: g[u]) {
			if (v - p) {
				sum[v] += sum[u];
				dfs_sum(v, u);
			}
		}
	}
	void dfs (int u, int p) {
		val.push_back(sum[u]);
		pos[u] = idx ++;
		for (int v: g[u]) {
			if (v - p) {
				dfs(v, u);
				sz[u] += sz[v];
			}
		}
	}
	void construct_diff_arr() {
		for (int i = n - 1; i > 0; i --) {
			val[i] -= val[i - 1];
			st.update(i, val[i]);
		}
		st.update(0, val[0]);
	}
	void run() {
		dfs_sum(0, -1);
		dfs(0, -1);
		construct_diff_arr();
	}
	void update (int s, ll x) {
		st.update(pos[s], x - a[s]);
		if (pos[s] + sz[s] < n) {
			st.update(pos[s] + sz[s], a[s] - x);
		}
		a[s] = x;
	}
	ll query (int s) {
		return st.query(0, pos[s] + 1);
	}
};
int main() {
	int n, q;
	cin >> n >> q;
	tree_trav_arr t;
	t.init(n);
	for (int i = 0; i < n; i ++) {
		ll v;
		cin >> v;
		t.add_val(i, v);
	}
	for (int i = 1; i <= n - 1; i ++) {
		int a, b;
		cin >> a >> b;
		-- a; -- b;
		t.add_edge(a, b);
	}
	t.run();
	while (q --) {
		int typ;
		cin >> typ;
		if (typ == 1) {
			int s;
			ll x;
			cin >> s >> x;
			-- s;
			t.update(s, x);
		}
		else {
			int s;
			cin >> s;
			-- s;
			cout << t.query(s) << endl;
		}
	}
}