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
struct graph_multi_source_bfs {
	const int INF = 1e6 + 5;
	int n, m, tgt;
	vector <vector <int>> g;
	vector <int> dist, dist2, par, ends;
	void init (int s, int w) {
		n = s;
		m = w;
		tgt = -1;
		g.resize(n);
		dist.assign(n, INF);
		dist2.resize(n, INF);
		par.resize(n);
		ends.assign(n, 0);
	}
	void add_edge (int u, int v) {
		g[u].push_back(v);
	}
	void bfs (vector <int> src) {
		queue <int> q;
		for (int s: src) {
			q.push(s);
			dist[s] = 0;
		}
		while (! q.empty()) {
			int u = q.front();
			q.pop();
			for (int v: g[u]) {
				if (dist[v] > dist[u] + 1) {
					dist[v] = dist[u] + 1;
					q.push(v);
				}
			}
		}
	}
	void bfs2 (int s) {
		queue <int> q;
		q.push(s);
		dist2[s] = 0;
		par[s] = -1;
		while (! q.empty()) {
			int u = q.front();
			q.pop();
			if (ends[u]) {
				tgt = u;
				return;
			}
			for (int v: g[u]) {
				if (dist2[v] > dist2[u] + 1) {
					if (dist[v] > dist2[u] + 1) {
						dist2[v] = dist2[u] + 1;
						par[v] = u;
						q.push(v);
					}
				}
			}
		}
	}
	string path() {
		string p;
		int u = tgt;
		while (par[u] + 1) {
			if (par[u] == u + 1) {
				p += 'L';
			}
			else if (par[u] == u - 1) {
				p += 'R';
			}
			else if (par[u] == u + m) {
				p += 'U';
			}
			else if (par[u] == u - m) {
				p += 'D';
			}
			u = par[u];
		}
		reverse (p.begin(), p.end());
		return p;
	}
};
int main() {
	int n, m, s;
	cin >> n >> m;
	graph_multi_source_bfs z;
	z.init(n * m, m);
	vector <vector <char>> a(n, vector <char> (m));
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < m; j ++) {
			cin >> a[i][j];
		}
	}
	vector <int> src;
	for (int i = 0; i < n; i ++) {
		for (int j = 0; j < m; j ++) {
			if (a[i][j] != '#') {
				if (i > 0 && a[i - 1][j] != '#') {
					z.add_edge(i * m + j, (i - 1) * m + j);
				}
				if (i < n - 1 && a[i + 1][j] != '#') {
					z.add_edge(i * m + j, (i + 1) * m + j);
				}
				if (j > 0 && a[i][j - 1] != '#') {
					z.add_edge(i * m + j, i * m + j - 1);
				}
				if (j < m - 1 && a[i][j + 1] != '#') {
					z.add_edge(i * m + j, i * m + j + 1);
				}
				if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
					z.ends[i * m + j] = 1;
				}
			}
			if (a[i][j] == 'M') {
				src.push_back(i * m + j);
			}
			if (a[i][j] == 'A') {
				s = i * m + j;
			}
		}
	}
	z.bfs(src);
	z.bfs2(s);
	if (z.tgt + 1) {
		cout << "YES" << endl;
		string p = z.path();
		cout << (int) p.length() << endl << p << endl;
	}
	else {
		cout << "NO" << endl;
	}
}