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

int sgn(ll x) {
  return (x > 0) - (x < 0);
}

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  
  string s;
  vector<pair<ll, int>> a;
  int cur = 0;
  pair<ll, int> zero;
  ll key = 811589153;
  while (getline(cin, s)) {
    int val = parseInts(s)[0];
    if (val == 0) zero = mp(val, cur);
    a.pb(mp(val * key, cur++));
  }
  auto oldA = a;
  int n = sz(a);
  forn (j, n * 10) {
    int ind = (find(all(a), oldA[j % n]) - a.begin());
    int dlt = oldA[j % n].fst % (n - 1);	
    forn (i, abs(dlt)) {
      int nextInd = (ind + sgn(dlt) + n) % n;
      swap(a[ind], a[nextInd]);
      ind = nextInd;
    }
  }
  int ind = find(all(a), zero) - a.begin();
  ll ans = 0;
  forn (i, 3) {
    ind = (ind + 1000) % n;
    ans += a[ind].fst;
  }
  cout << ans << "\n";
  
  return 0;
}
