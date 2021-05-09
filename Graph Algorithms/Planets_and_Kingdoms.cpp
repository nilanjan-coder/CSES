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
struct graph_kosaraju {
	int n, idx;
	vector <vector <int>> g, gr, components;
	vector <int> used, order, component;
	map <int, int> comp;
	void init (int s) {
		n = s;
		g.resize(n);
		gr.resize(n);
		components.clear();
		used.clear();
		order.clear();
		component.clear();
		comp.clear();
		idx = -1;
	}
	void add_edge (int u, int v) {
		g[u].push_back(v);
		gr[v].push_back(u);
	}
	void dfs1 (int u) { // topsort
		used[u] = 1;
		for (int v: g[u]) {
			if (used[v] == 0) {
				dfs1(v);
			}
		}
		order.push_back(u);
	}
	void dfs2 (int u) {
		used[u] = 1;
		component.push_back(u);
		comp[u] = idx;
		for (int v: gr[u]) {
			if (used[v] == 0) {
				dfs2(v);
			}
		}
	}
	void run() {
		used.assign(n, 0);
		for (int i = 0; i < n; i ++) {
			if (used[i] == 0) {
				dfs1(i);
			}
		}
		used.assign(n, 0);
		for (int i = n - 1; i >= 0; i --) {
			int u = order[i];
			if (used[u] == 0) {
				component.clear();
				++ idx;
				dfs2(u);
				components.push_back(component);
			}
		}
	}
};
int main() {
	int n, m;
	cin >> n >> m;
	graph_kosaraju z;
	z.init(n);
	while (m --) {
		int a, b;
		cin >> a >> b;
		-- a; -- b;
		z.add_edge(a, b);
	}
	z.run();
	cout << (int) z.components.size() << endl;
	for (int i = 0; i < n; i ++) {
		cout << z.comp[i] + 1 << " ";
	}
}