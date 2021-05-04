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
struct tree_lca_lift {
	int n, lgn;
	vector <vector <int>> g, spt;
	vector <int> dep;
	void init (int s) {
		n = s;
		lgn = log2(n) + 1;
		dep.resize(n);
		g.resize(n);
		spt.assign(n, vector <int> (lgn, -2));
	}
	void add_edge (int u, int v) {
		g[u].push_back(v);
		g[v].push_back(u);
	}
	void dfs (int u, int p) {
		dep[u] = (p == -2) ? 0 : (dep[p] + 1);
		spt[u][0] = p;
		for (int i = 1; i < lgn; i ++) {
			if (spt[u][i - 1] == -2)  {
				spt[u][i] = -2;
			}
			else {
				spt[u][i] = spt[spt[u][i - 1]][i - 1];
			}
		}
		for (int v: g[u]) {
			if (v - p) {
				dfs(v, u);
			}
		}
	}
	int lift (int u, int d) {
		for (int i = lgn - 1; i >= 0 && u >= 0; i --) {
			if ((1 << i) <= d) {
				u = spt[u][i];
				d -= (1 << i);
			}
		}
		return u;
	}
	int lca (int u, int v) {
		if (dep[u] < dep[v]) {
			swap(u, v);
		}
		int d = dep[u] - dep[v];
		u = lift(u, d);
		if (v == u) {
			return u;
		}
		else {
			for (int i = lgn - 1; i >= 0; i --) {
				if (spt[v][i] - spt[u][i]) {
					v = spt[v][i];
					u = spt[u][i];
				}
			}
			return spt[u][0];
		}
	}
	int dist (int u, int v) {
		return dep[u] + dep[v] - 2 * dep[lca(u, v)];
	}
};
int main() {
	int n, q;
	cin >> n >> q;
	tree_lca_lift t;
	t.init(n);
	for (int i = 1; i <= n - 1; i ++) {
		int p;
		cin >> p;
		-- p;
		t.add_edge(i, p);
	}
	t.dfs(0, -2);
	while (q --) {
		int x, k;
		cin >> x >> k;
		-- x;
		cout << t.lift(x, k) + 1 << endl;
	}
}