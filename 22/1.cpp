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

const int TURN[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

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

int add(int a, int b, int mod) {
	a += b;
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
	int m = 0;
	while (getline(cin, s)) {
		if (s.empty())
			break;
		m = max(m, sz(s));
		a.pb(s);
	}
	int n = sz(a);
	forn (i, n)
		while (sz(a[i]) < m)
			a[i].pb(' ');
	cin >> s;
	auto v = parseInts(s);
	int x = 0, y = a[0].find('.'), dir = 0;

	string dirs;
	for (char c : s) 
		if (c == 'L' || c == 'R')
			dirs.pb(c);
	forn (i, sz(v)) {
		int steps = v[i];
		forn (j, steps) {
			int curX = x, curY = y;
			do {
				curX = add(curX, TURN[dir][0], n);
				curY = add(curY, TURN[dir][1], m);
			} while (a[curX][curY] == ' ');
			if (a[curX][curY] == '.')
				x = curX, y = curY;
			else
				break;
		}
		if (i != sz(v) - 1) {
			dir = add(dir, (dirs[i] == 'L' ? -1 : 1), 4);
		}
	}
	cout << (x + 1) * 1000 + (y + 1) * 4 + dir << "\n";
	return 0;
}
