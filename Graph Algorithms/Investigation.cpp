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
struct graph_dijkstra_daspg_topsort_dp {
	const ll INF = 1e16, MOD = 1e9 + 7;
	int n;
	vector <vector <pair <ll, int>>> g, g2;
	vector <vector <int>> daspg, daspg2;
	vector <int> vis, ts;
	vector <ll> dist, dist2, cnt, nin, nax;
	void init (int s) {
		n = s;
		g.resize(n);
		g2.resize(n);
		daspg.resize(n);
		daspg2.resize(n);
		dist.assign(n, INF);
		dist2.assign(n, INF);
		ts.clear();
		cnt.assign(n, 0);
		nin.assign(n, INF);
		nax.assign(n, -INF);
	}
	void add_edge (int a, int b, ll c) {
		g[a].push_back({c, b});
		g2[b].push_back({c, a});
	}
	void dijkstra() {
		priority_queue <pair <ll, int>, vector <pair <ll, int>>, greater <pair <ll, int>>> pq;
		pq.push({0, 0});
		dist[0] = 0;
		while (! pq.empty()) {
			pair <ll, int> u = pq.top();
			pq.pop();
			if (vis[u.second]) continue;
			vis[u.second] = 1;
			for (pair <ll, int> v: g[u.second]) {
				if (dist[u.second] + v.first < dist[v.second]) {
					dist[v.second] = dist[u.second] + v.first;
					pq.push({dist[v.second], v.second});
				}
			}
		}
	}
	void dijkstra2() {
		priority_queue <pair <ll, int>, vector <pair <ll, int>>, greater <pair <ll, int>>> pq;
		pq.push({0, n - 1});
		dist2[n - 1] = 0;
		while (! pq.empty()) {
			pair <ll, int> u = pq.top();
			pq.pop();
			if (vis[u.second]) continue;
			vis[u.second] = 1;
			for (pair <ll, int> v: g2[u.second]) {
				if (dist2[u.second] + v.first < dist2[v.second]) {
					dist2[v.second] = dist2[u.second] + v.first;
					pq.push({dist2[v.second], v.second});
				}
			}
		}
	}
	void construct_daspg() {
		for (int u = 0; u < n; u ++) {
			for (pair <ll, int> v: g[u]) {
				if (dist[u] + v.first + dist2[v.second] == dist[n - 1]) {
					daspg[u].push_back(v.second);
					daspg2[v.second].push_back(u);
				}
			}
		}
	}
	void dfs (int u) {
		vis[u] = 1;
		for (int v: daspg[u]) {
			if (vis[v] == 0) {
				dfs(v);
			}
		}
		ts.push_back(u);
	}
	void topsort_dp() {
		for (int i = 0; i < n; i ++) {
			if (vis[i] == 0) {
				dfs(i);
			}
		}
		reverse(ts.begin(), ts.end());
		cnt[0] = nin[0] = nax[0] = 1;
		for (int i = 0; i < n; i ++) {
			int u = ts[i];
			for (int v: daspg2[u]) {
				cnt[u] = (cnt[u] + cnt[v]) % MOD;
				nin[u] = min(nin[u], nin[v] + 1);
				nax[u] = max(nax[u], nax[v] + 1);
			}
		}
	}
	void run() {
		vis.assign(n, 0);
		dijkstra();
		vis.assign(n, 0);
		dijkstra2();
		vis.assign(n, 0);
		construct_daspg();
		topsort_dp();
	}
};
int main() {
	int n, m;
	cin >> n >> m;
	graph_dijkstra_daspg_topsort_dp z;
	z.init(n);
	while (m --) {
		int a, b;
		ll c;
		cin >> a >> b >> c;
		-- a; -- b;
		z.add_edge(a, b, c);
	}
	z.run();
	cout << z.dist[n - 1] << " " << z.cnt[n - 1] << " " << z.nin[n - 1] - 1 << " " << z.nax[n - 1] - 1 << endl;
}