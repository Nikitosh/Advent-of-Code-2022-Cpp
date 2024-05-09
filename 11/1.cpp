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

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  
  string s;
  vector<vi> v;
  vi tst, tru, fls;
  vector<std::function<int(int)>> op;
  while (getline(cin, s)) {
    auto u = parseInts(s);
    if (s.empty())
      continue;
    if (s[2] == 'S') {
      v.pb(u);
    } else if (s[2] == 'O') {
      bool mul = find(all(s), '*') != s.end();
      auto f = [mul](int x, int y) {
        return mul ? x * y : x + y;
      };
      op.pb([f, u](int x) {
        return u.empty() ? f(x, x) : f(x, u[0]);
      });
    } else if (s[2] == 'T') {
      tst.pb(u[0]);
    } else if (s[4] == 'I' && s[7] == 't') {
      tru.pb(u[0]);
    } else if (s[4] == 'I' && s[7] == 'f') {
      fls.pb(u[0]);
    }
  }
  int n = sz(v);

  const int ROUNDS = 20;
  vi ans(n);
  forn (i, ROUNDS) {
    forn (j, n) {
      ans[j] += sz(v[j]);
      for (int k : v[j]) {
        k = op[j](k) / 3;
        int ind = (k % tst[j] == 0 ? tru[j] : fls[j]);
        v[ind].pb(k);
      }
      v[j].clear();
    }
  }
  sort(all(ans));
  reverse(all(ans));
  cout << ans[0] * 1ll * ans[1] << "\n";
  
  return 0;
}
