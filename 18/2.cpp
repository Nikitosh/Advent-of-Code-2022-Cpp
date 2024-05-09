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
      if (i != 0 && s[i - 1] == '-')
        x *= -1;
      res.pb(x);
      i = j - 1;
    }
  }
  return res;
}

const int MAX = 50;

int dfs(int x, int y, int z, set<vi>& used, const set<vi>& figure) {
  if (min(x, min(y, z)) < -1 || max(x, max(y, z)) >= MAX)
    return 0;
  int res = 0;
  used.insert({x, y, z});
  forab (dx, -1, 2)
    forab (dy, -1, 2)
      forab (dz, -1, 2) {
        if (abs(dx) + abs(dy) + abs(dz) != 1)
          continue;
        if (figure.count({x + dx, y + dy, z + dz}))
          res++;
        if (!used.count({x + dx, y + dy, z + dz}))
          res += dfs(x + dx, y + dy, z + dz, used, figure);
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
  set<vi> figure;
  while (getline(cin, s)) {
    auto v = parseInts(s);
    figure.insert(v);
  }
  set<vi> used = figure;
  cout << dfs(-1, -1, -1, used, figure) << "\n";
  return 0;
}
