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

bool good(int x, int y, int n, int m) {
  return x >= 0 && x < n && y >= 0 && y < m; 
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
  const int ROUNDS = 1000;
  int n = sz(a), m = sz(a[0]);
  vector<string> copy(n + 2 * ROUNDS, string(m + 2 * ROUNDS, '.'));
  forn (i, n)
    forn (j, m)
      copy[i + ROUNDS][j + ROUNDS] = a[i][j];
  a = copy;
  n += 2 * ROUNDS, m += 2 * ROUNDS;
  map<pii, vector<pii>> nxt;
  forn (q, ROUNDS) {
    forn (i, n) {
      forn (j, m) {
        if (a[i][j] == '.')
          continue;
        int cnt = 0;
        forab (x, -1, 2) {
          forab (y, -1, 2) {
            if (x == 0 && y == 0)
              continue;
            int nx = i + x, ny = j + y;
            if (good(nx, ny, n, m) && a[nx][ny] == '#')
              cnt++;
          }
        }
        if (cnt == 0) {
          nxt[mp(i, j)].pb(mp(i, j));
          continue;
        }
        bool was = 0;
        forn (g, 4) {
          int ind = (q + g) % 4;
          cnt = 0;
          forab (x, -1, 2) {
            int nx = i + (TURN[ind][0] == 0 ? x : TURN[ind][0]);
            int ny = j + (TURN[ind][1] == 0 ? x : TURN[ind][1]);
            if (good(nx, ny, n, m) && a[nx][ny] == '#')
              cnt++;
          }
          int nx = i + TURN[ind][0];
          int ny = j + TURN[ind][1];
          if (good(nx, ny, n, m) && cnt == 0) {
            was = 1;
            nxt[mp(nx, ny)].pb(mp(i, j));
            break;
          }
        }
        if (!was) {
          nxt[mp(i, j)].pb(mp(i, j));
        }
      }
    }
    auto oldA = a;
    forn (i, n)
      forn (j, m)
        a[i][j] = '.';
    for (auto& [cell, vals] : nxt) {
      if (sz(vals) > 1) {
        for (auto& np : vals)
          a[np.fst][np.snd] = '#';
      } else {
        a[cell.fst][cell.snd] = '#';
      }
    }
    nxt.clear();
    if (a == oldA) {
      cout << q + 1 << "\n";
      break;
    }
  }

  return 0;
}
