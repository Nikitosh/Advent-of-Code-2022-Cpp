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

const char* DIRS = "^>v<";
const int TURN[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

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

int norm(int a, int mod) {
	return a < 0 ? a + mod : (a >= mod ? a - mod : a);
}

int main() {
#ifdef LOCAL
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
#endif
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	
	string s;
	vector<string> a;
	while (getline(cin, s)) {
		a.pb(s);
	}
	int n = sz(a), m = sz(a[0]);
	set<pair<pii, int>> poss, nextPoss;
	forn (i, n) {
		forn (j, m) {
			auto k = strchr(DIRS, a[i][j]);
			if (k != nullptr) {
				poss.insert(mp(mp(i, j), (int) (k - DIRS)));
			}
		}
	}
	set<pii> ts = {mp(0, 1)}, nextTs;
	int timer = 0;
	vector<pii> dests = {mp(n - 1, m - 2), mp(0, 1), mp(n - 1, m - 2)};
	int destIt = 0;
	while (destIt < 3) {
		timer++;
		for (auto [pos, dir] : poss) {
			int nx = pos.fst + TURN[dir][0], ny = pos.snd + TURN[dir][1];
			nx = norm(nx - 1, n - 2) + 1;
			ny = norm(ny - 1, m - 2) + 1;
			nextPoss.insert(mp(mp(nx, ny), dir));	
		}
		for (auto& [x, y] : ts) {
			forn (g, 5) {
				int nx = x, ny = y;
				if (g < 4)
					nx += TURN[g][0], ny += TURN[g][1];
				if (nx >= 0 && ny >= 0 && nx < n && ny < m && a[nx][ny] != '#') {
					auto it = nextPoss.lower_bound(mp(mp(nx, ny), -1));
					if (it != nextPoss.end() && it->fst == mp(nx, ny))
						continue;
					nextTs.insert(mp(nx, ny));
				}		
			}
		}
		poss = nextPoss;
		nextPoss.clear();
		ts = nextTs;
		nextTs.clear();
		if (ts.count(dests[destIt]))
			ts = {dests[destIt++]};
	}
	cout << timer << "\n";

	return 0;
}
