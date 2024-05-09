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

const int INF = 1e9;

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
  int n = 0, f = 0;
  map<string, int> num;
  map<int, int> mFl;
  map<string, vector<string>> gstr;
  vector<string> strs;
  vi nonZeroFlows, flowToInd;
  while (getline(cin, s)) {
    string t = s.substr(6, 2);
    int r = parseInts(s)[0];
    if (r != 0) {
      nonZeroFlows.pb(r);
      flowToInd.pb(f++);
    }
    else
      flowToInd.pb(-1);
    int ind = s.find(' ', s.find("valve")) + 1;
    vector<string> v;
    while (ind < sz(s)) {
      v.pb(s.substr(ind, 2));
      ind += 4;
    }
    gstr[t] = v;
    strs.pb(t);
    num[t] = n++;
  }
  vector<vi> g(n);
  forn (i, n) {
    for (auto& str : gstr[strs[i]])
      g[i].pb(num[str]);
  }
  vi dlt(1 << f);
  forn (mask, 1 << f) {
    forn (i, f)
      if ((mask >> i) & 1) {
        dlt[mask] = dlt[mask ^ (1 << i)] + nonZeroFlows[i];
        break;
      }
  }

  vector<vector<vi>> dp(n, vector<vi>(n, vi(1 << f, -INF))), newDp(n, vector<vi>(n, vi(1 << f, -INF)));
  dp[num["AA"]][num["AA"]][0] = 0;
  const int ROUNDS = 26;
  forn (round, ROUNDS) {
    cerr << round << "\n";
    forn (i, n)
      forn (j, n)
        fill(all(newDp[i][j]), -INF);
    forn (v, n)
      forn (u, v + 1)
        forn (mask, 1 << f) {
          if (dp[v][u][mask] < 0) continue;
          forn (x, sz(g[v]) + 1)
            forn (y, sz(g[u]) + 1) {
              int nV = v, nU = u, nMask = mask;
              if (x < sz(g[v]))
                nV = g[v][x];
              else if (int ind = flowToInd[v]; ind != -1 && !((mask >> ind) & 1))
                nMask |= (1 << ind);
              if (y < sz(g[u]))
                nU = g[u][y];
              else if (int ind = flowToInd[u]; ind != -1 && !((mask >> ind) & 1))
                nMask |= (1 << ind);
              if (nV < nU) swap(nV, nU);
              newDp[nV][nU][nMask] = max(newDp[nV][nU][nMask], dp[v][u][mask] + dlt[mask]);
            }
        }
    dp.swap(newDp);
  }
  int ans = 0;
  forn (i, n)
    forn (j, n)
      ans = max(ans, *max_element(all(dp[i][j])));
  cout << ans << "\n";
  return 0;
}
