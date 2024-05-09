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

const int MAX = 100000, W = 7;

int findFirstEmpty(const vector<vi>& a) {
  forn (i, MAX)
    if (accumulate(all(a[i]), 0) == 0)
      return i;
  return 0;
}

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  
  string s;
  vector<vector<string>> figures = {
    {"1111"}, 
    {"010", "111", "010"},
    {"001", "001", "111"},
    {"1", "1", "1", "1"},
    {"11", "11"}
  };
  cin >> s;
  int curF = 0;
  int curS = 0;
  vector<vi> a(MAX, vi(W));
  int MIN_ROUNDS = 10000;
  vi ansY(MIN_ROUNDS);
  map<pii, pii> was;
  int dltRounds = 0, dltHeight = 0;
  forn (qq, MIN_ROUNDS) {
    ansY[qq] = findFirstEmpty(a);
    auto it = was.find(mp(curF, curS));
    if (it != was.end()) {
      dltRounds = qq - it->snd.fst;
      dltHeight = ansY[qq] - it->snd.snd;
    }
    was[mp(curF, curS)] = mp(qq, ansY[qq]);
    int y = ansY[qq] + 3;
    int x = 2;
    int h = figures[curF].size();
    int w = figures[curF][0].size();
    bool run = 1;
    while (run) {
      forn (g, 2) {
        int oldX = x, oldY = y;
        if (g == 0) {
          if (s[curS] == '<')
            x--;
          else
            x++;
          curS = (curS + 1) % sz(s);
        } else {
          y--;
        }
        bool ok = x >= 0 && x + w <= W && y >= 0;
        if (ok) {
          forn (i, h)
            forn (j, w) {
              if (figures[curF][i][j] == '1' && a[y + h - 1 - i][x + j] == 1) {
                ok = 0;
                break;
              }
            }
        }
        if (!ok) {
          x = oldX, y = oldY;
          if (g == 1) {
            run = 0;
          }
        }
      }
    }
    forn (i, h)
      forn (j, w)
        if (figures[curF][i][j] == '1')
          a[y + h - 1 - i][x + j] = 1;
    curF = (curF + 1) % sz(figures);
  }
  const ll ROUNDS = 1000000000000;
  cout << ROUNDS / dltRounds * dltHeight + ansY[ROUNDS % dltRounds] << "\n";
  
  return 0;
}
