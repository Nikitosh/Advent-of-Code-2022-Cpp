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

const int MAX = 3e7;

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
	while (getline(cin, s)) {
		auto v = parseInts(s);
		u.pb(v);
	}
	const int y = 2000000;
	int ans = 0;
	forab (x, -MAX, MAX + 1) {
		bool ok = 0, d = 1;
		for (auto& v : u) {
			int dst = abs(v[2] - v[0]) + abs(v[3] - v[1]);
			if (v[2] == x && v[3] == y) {
				d = 0;
				break;
			}
			int cur = abs(x - v[0]) + abs(y - v[1]);
			ok |= (cur <= dst);
		}
		ans += (ok && d);
	}
	cout << ans << "\n";

	return 0;
}
