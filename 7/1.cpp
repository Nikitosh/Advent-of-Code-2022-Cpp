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

const int MAX_SIZE = 100000;

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
  map<vector<string>, ll> m;
  vector<string> path;
  while(getline(cin, s)) {
    if (s[0] == '$' && s[2] == 'c') {
      s = s.substr(5, sz(s) - 5);
      if (s == "..")
        path.pop_back();
      else
        path.pb(s);
    }
    auto v = parseInts(s);
    if (!v.empty()) {
      vector<string> path2 = path;
      while (!path2.empty()) {
        m[path2] += v[0];
        path2.pop_back();
      }
    }
  }
  ll ans = 0;
  for (const auto& [_, siz] : m)
    if (siz < MAX_SIZE)
      ans += siz;
  cout << ans << "\n";

  return 0;
}
