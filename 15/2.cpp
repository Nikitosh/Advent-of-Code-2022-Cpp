#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define sz(x) (int) ((x).size())
#define forn(i, n) for (int i = 0; i < (n); ++i)
#define fornr(i, n) for (int i = (n) - 1; i >= 0; --i)
#define forab(i, a, b) for (int i = (a); i < (b); ++i)
#define all(c) (c).begin(), (c).end()

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) static_cast<void>(0)
#endif

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using uint = unsigned int;
using vi = vector<int>;
using pii = pair<int, int>;

const int MAX = 4000000;

vi parseInts(const string& s) {
	int n = sz(s);
	vi res;
	forn (i, n) {
		if (isdigit(s[i])) {
			int j = i, x = 0;
			while (j < n && isdigit(s[j])) {
				x = 10 * x + s[j] - '0';
				j++;
			}
			if (i != 0 && s[i - 1] == '-')
				x *= -1;
			res.pb(x);
			i = j - 1;
		}
	}
	return res;
}

int main() {
#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	
	string s;
	vector<vi> u;
	set<pii> cands;
	while (getline(cin, s)) {
		auto v = parseInts(s);
		u.pb(v);
		int dst = abs(v[2] - v[0]) + abs(v[3] - v[1]) + 1;
		forab (dltX, -dst, dst + 1) {
			int x = v[0] + dltX;
			cands.insert(mp(x, v[1] + dst - abs(dltX)));
			cands.insert(mp(x, v[1] - (dst - abs(dltX))));
		}
	}
	for (auto& [x, y] : cands) {
		if (x < 0 || y < 0 || x > MAX || y > MAX)
			continue;
		bool ok = 0, d = 1;
		for (auto& v : u) {
			if (v[2] == x && v[3] == y) {
				d = 0;
				break;
			}
			int dst = abs(v[2] - v[0]) + abs(v[3] - v[1]);
			int cur = abs(x - v[0]) + abs(y - v[1]);
			if (cur <= dst)
				ok = 1;
		}
		if (d && !ok) {
			cout << x * 1ll * MAX + y << "\n";
		}
	}
	return 0;
}
