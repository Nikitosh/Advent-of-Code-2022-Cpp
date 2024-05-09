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

set<pair<int, pair<vi, vi>>> was;

void go(int k, vi cnts, vi robots, const vector<vi>& costs, int n, int& maxx) {
  if (robots[0] > max(max(costs[0][0], costs[1][0]), max(costs[2][0], costs[3][0])) || was.count(mp(k, mp(cnts, robots))))
    return;
  if (k == n) {
    maxx = max(maxx, cnts[3]);
    return;
  }
  for (int i = 3; i >= -1; i--) {
    auto newCnts = cnts;
    auto newRobots = robots;
    if (i != -1) {
      bool ok = 1;
      forn (j, sz(costs[i])) {
        if (newCnts[j] < costs[i][j]) {
          ok = 0;
          break;
        }
        newCnts[j] -= costs[i][j];
      }
      if (!ok)
        continue;
      newRobots[i]++;
    }
    forn (j, 4)
      newCnts[j] += robots[j];
    go(k + 1, newCnts, newRobots, costs, n, maxx);	
    if (i >= 2)
      break;
  }
  was.insert(mp(k, mp(cnts, robots)));
}

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  
  int ans = 1; 
  forn (i, 3) {
    string s;
    getline(cin, s);
    auto v = parseInts(s);
    vector<vi> costs = {{v[1]}, {v[2]}, {v[3], v[4]}, {v[5], 0, v[6]}};
    was.clear();
    int maxx = 0;
    go(0, {0, 0, 0, 0}, {1, 0, 0, 0}, costs, 32, maxx);	
    ans *= maxx;	
  }
  cout << ans << "\n";

  return 0;
}
