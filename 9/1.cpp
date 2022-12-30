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

const char* DIRS = "UDLR";
const int TURN[4][2] = {{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

int main() {
#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	
	string s;
	
	int hx = 0, hy = 0, tx = 0, ty = 0;
	set<pii> ts;
	ts.insert(mp(tx, ty));
	while  (getline(cin, s)) {
		int dir = strchr(DIRS, s[0]) - DIRS;
		int k = atoi(s.substr(2, sz(s) - 2).c_str());
		forn (i, k) {
			hx += TURN[dir][0], hy += TURN[dir][1];
			if (abs(tx - hx) > 1 || abs(ty - hy) > 1) {
				tx = int(round((2 * hx + tx) / 3.));
				ty = int(round((2 * hy + ty) / 3.));
			}
			ts.insert(mp(tx, ty));
		}
	}
	cout << sz(ts) << "\n";
	
	return 0;
}
