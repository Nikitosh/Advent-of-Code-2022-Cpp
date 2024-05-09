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

const int N = 1005, START_X = 500, START_Y = 0;

int a[N][N];

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
  int maxY = -1;
  while (getline(cin, s)) {
    auto v = parseInts(s);
    for (int g = 2; g < sz(v); g += 2)
      forab (i, min(v[g], v[g - 2]), max(v[g], v[g - 2]) + 1)
        forab (j, min(v[g + 1], v[g - 1]), max(v[g + 1], v[g - 1]) + 1)
          a[i][j] = 1; 
    for (int g = 0; g < sz(v); g += 2)
      maxY = max(maxY, v[g + 1]);
  }
  int ans = 0;
  while (!a[START_X][START_Y]) {
    int x = START_X, y = START_Y; 
    bool overflow = 0;
    while (!a[x][y]) {
      bool was = 0;
      for (int dx : {0, -1, 1}) {
        if (a[x + dx][y + 1] == 0) {
          x += dx, y++;
          was = 1;
          break;
        }
      }
      if (y > maxY) {
        overflow = 1;
        break;
      }
      if (!was)
        break;
    }
    if (overflow)
      break;
    a[x][y] = 1;
    ans++;
  }
  cout << ans << "\n";
  
  return 0;
}
