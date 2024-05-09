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
  
  vector<string> s;
  string t;
  while (getline(cin, t)) {
    s.pb(t);
  }
  int n = sz(s), m = sz(s[0]);
  queue<pii> q;
  vector<vi> d(n, vi(m, n * m));
  int fX = 0, fY = 0;
  forn (i, n)
    forn (j, m) {
      if (s[i][j] == 'E') {
        s[i][j] = 'z';
        fX = i, fY = j;
      }
      if (s[i][j] == 'S' || s[i][j] == 'a') {
        s[i][j] = 'a';
        d[i][j] = 0;
        q.push(mp(i, j));				
      }
    }
  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();
    forn (g, 4) {
      int nX = x + TURN[g][0], nY = y + TURN[g][1];
      if (nX >= 0 && nY >= 0 && nX < n && nY < m && s[nX][nY] <= s[x][y] + 1 && d[nX][nY] > d[x][y] + 1) {
        d[nX][nY] = d[x][y] + 1;
        q.push(mp(nX, nY));
      }
    }
  }
  cout << d[fX][fY] << "\n";

  return 0;
}
