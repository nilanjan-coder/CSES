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
struct string_hashing1 {
	const ll a = 1e9 + 5, b = 1e9 + 7;
	vector <ll> h, p;
	void init (string s) {
		int n = s.length();
		h.resize(n);
		p.resize(n);
		h[0] = s[0];
		p[0] = 1;
		for (int i = 1; i < n; i ++) {
			h[i] = (h[i - 1] * a % b + s[i]) % b;
			p[i] = p[i - 1] * a % b;
		}
	}
	ll hash (int i, int j) {
		if (i == 0) {
			return h[j];
		}
		else {
			return (h[j] - h[i - 1] * p[j - i + 1] % b + b) % b;
		}
	}
};
struct string_hashing2 {
	const ll a = 1e9 + 5, b = 1e9 + 9;
	vector <ll> h, p;
	void init (string s) {
		int n = s.length();
		h.resize(n);
		p.resize(n);
		h[0] = s[0];
		p[0] = 1;
		for (int i = 1; i < n; i ++) {
			h[i] = (h[i - 1] * a % b + s[i]) % b;
			p[i] = p[i - 1] * a % b;
		}
	}
	ll hash (int i, int j) {
		if (i == 0) {
			return h[j];
		}
		else {
			return (h[j] - h[i - 1] * p[j - i + 1] % b + b) % b;
		}
	}
};
int main() {
	string s;
	cin >> s;
	int n = s.length();
	string_hashing1 z1;
	string_hashing2 z2;
	z1.init(s);
	z2.init(s);
	int ans = 0;
	for (int len = 1; len <= n; len ++) {
		bool check = true;
		int i;
		for (i = len; i + len - 1 < n; i += len) {
			if (z1.hash(0, len - 1) != z1.hash(i, i + len - 1) || z2.hash(0, len - 1) != z2.hash(i, i + len - 1)) {
				check = false;
				break;
			}
		}
		if (check) {
			if (i == n) {
				ans = len;
				break;
			}
			else {
				int len0 = len;
				len = n - i;
				if (z1.hash(0, len - 1) == z1.hash(i, i + len - 1) && z2.hash(0, len - 1) == z2.hash(i, i + len - 1)) {
					ans = len0;
					break;
				}
				len = len0;
			}
		}
	}
	int mul = 1;
	while (ans * mul < n) {
		cout << ans * mul << " ";
		++ mul;
	}
	-- mul;
	ans *= mul;
	for (int len = ans + 1; len <= n - 1; len ++) {
		int len0 = n - len;
		if (z1.hash(0, len0 - 1) == z1.hash(n - len0, n - 1) && z2.hash(0, len0 - 1) == z2.hash(n - len0, n - 1)) {
			cout << len << " ";
		}
	}
	cout << n << endl;
}