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
	int ans = 0;
	while (getline(cin, s)) {
		auto v = parseInts(s);
		ans += ((v[0] <= v[2] && v[1] >= v[3]) || (v[2] <= v[0] && v[3] >= v[1]));
	}
	cout << ans << "\n";
	
	return 0;
}
