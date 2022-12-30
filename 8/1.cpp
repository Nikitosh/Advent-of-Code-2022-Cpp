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

const int TURN[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

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
	int n = sz(a);
	int m = sz(a[0]);
	int ans = 0;
	forn (i, n) {
		forn (j, m) {
			bool ok = 0;
			forn (g, 4) {
				int x = i + TURN[g][0], y = j + TURN[g][1];
				bool was = 0;
				while (x >= 0 && y >= 0 && x < n && y < m) {
					if (a[x][y] >= a[i][j]) {
						was = 1;
						break;
					}
					x += TURN[g][0], y += TURN[g][1];
				}
				ok |= !was;
			}
			ans += ok;
		}
	}
	cout << ans << "\n";
	return 0;
}
