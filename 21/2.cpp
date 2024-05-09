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

pair<ll, bool> get(const string& s, map<string, pair<char, pair<string, string>>>& deps, map<string, pair<ll, bool>>& go) {
  if (go.count(s))
    return go[s];
  auto [op1, humn1] = get(deps[s].snd.fst, deps, go);
  auto [op2, humn2] = get(deps[s].snd.snd, deps, go);
  char c = deps[s].first;
  if (c == '+')
    op1 += op2; 
  if (c == '-')
    op1 -= op2; 
  if (c == '*')
    op1 *= op2; 
  if (c == '/')
    op1 /= op2;
  return go[s] = mp(op1, humn1 || humn2);
}

ll calc(string s, ll value, map<string, pair<char, pair<string, string>>>& deps, map<string, pair<ll, bool>>& go) {
  if (s == "humn")
    return value;
  string depName = deps[s].snd.fst;
  ll other = get(deps[s].snd.snd, deps, go).fst;
  if (!get(deps[s].snd.fst, deps, go).snd) {
    depName = deps[s].snd.snd;
    other = get(deps[s].snd.fst, deps, go).fst;
  }
  char c = deps[s].first;
  if (c == '+')
    return calc(depName, value - other, deps, go);
  if (c == '-') {
    if (depName == deps[s].snd.fst)
      return calc(depName, value + other, deps, go);
    return calc(depName, other - value, deps, go);
  }
  if (c == '*')
    return calc(depName, value / other, deps, go);
  if (c == '/') {
    if (depName == deps[s].snd.fst)
      return calc(depName, value * other, deps, go);
    return calc(depName, other / value, deps, go);
  }
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
  map<string, pair<char, pair<string, string>>> deps;
  map<string, pair<ll, bool>> go;
  while (getline(cin, s)) {
    auto name = s.substr(0, 4);
    auto v = parseInts(s);
    if (!v.empty()) 
      go[name] = mp(v[0], s.substr(0, 4) == "humn");
    else
      deps[name] = mp(s[11], mp(s.substr(6, 4), s.substr(13, 4)));
  }
  if (!get(deps["root"].snd.fst, deps, go).snd)
    swap(deps["root"].snd.fst, deps["root"].snd.snd);
  cout << calc(deps["root"].snd.fst, get(deps["root"].snd.snd, deps, go).fst, deps, go) << "\n";
  return 0;
}
