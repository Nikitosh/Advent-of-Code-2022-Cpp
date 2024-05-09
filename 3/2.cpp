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

char fromCode(int c) {
  if (c < 26)
    return 'a' + c;
  return 'A' + c - 26;
}

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  
  string s, t, r;
  int ans = 0;
  while (cin >> s) {
    cin >> t >> r;
    forn (i, 52)
      if (s.find(fromCode(i)) != string::npos
        && t.find(fromCode(i)) != string::npos
        && r.find(fromCode(i)) != string::npos) 
        ans += i + 1;
  }
  cout << ans << "\n";
  
  return 0;
}
