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
const int L = 50;

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

int add(int a, int b, int mod) {
  return norm(a + b, mod);
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
    if (s.empty()) {
      break;
    }
    a.pb(s);
  }
  vi stX = {0, L, 2 * L, 2 * L, 3 * L, 0};
  vi stY = {L, L, L, 0, 0, 2 * L};
  pii go[6][4] = {
    {mp(5, 0), mp(1, 0), mp(3, 2), mp(4, 1)},
    {mp(5, 3), mp(2, 0), mp(3, 3), mp(0, 0)},
    {mp(5, 2), mp(4, 1), mp(3, 0), mp(1, 0)},
    {mp(2, 0), mp(4, 0), mp(0, 2), mp(1, 1)},
    {mp(2, 3), mp(5, 0), mp(0, 3), mp(3, 0)},
    {mp(2, 2), mp(1, 1), mp(0, 0), mp(4, 0)},			
  };
  cin >> s;
  auto v = parseInts(s);
  int x = 0, y = 0, dir = 0, side = 0;

  string dirs;
  for (char c : s) 
    if (c == 'L' || c == 'R')
      dirs.pb(c);
  forn (i, sz(v)) {
    int steps = v[i];
    forn (j, steps) {
      int nX = x + TURN[dir][0], nY = y + TURN[dir][1], nDir = dir, nSide = side;
      if (nX < 0 || nY < 0 || nX >= L || nY >= L) {
        nX = norm(nX, L);
        nY = norm(nY, L);
        forn (g, go[side][dir].snd) {
          int newX = nY;
          nY = L - 1 - nX;
          nX = newX;
        }
        nSide = go[side][dir].fst;
        nDir = add(dir, go[side][dir].snd, 4);
      }
      if (a[stX[nSide] + nX][stY[nSide] + nY] == '#')
        break;
      x = nX, y = nY, dir = nDir, side = nSide;
    }
    if (i != sz(v) - 1)
      dir = add(dir, (dirs[i] == 'L' ? -1 : 1), 4);
  }
  cout << (stX[side] + x + 1) * 1000 + (stY[side] + y + 1) * 4 + dir << "\n";
  return 0;
}
