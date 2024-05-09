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

struct Node {
  int value = -1;
  vector<Node*> children;
  Node() {}
  Node(int value_): value(value_) {} 
  Node(vector<Node*> children_): children(children_) {}
};

Node* parse(const string& s, int& ind) {
  if (s[ind] == '[') {
    Node* cur = new Node();
    ind++;
    while (s[ind] != ']') {
      cur->children.pb(parse(s, ind));
      if (s[ind] == ',')
        ind++;
    }
    ind++;
    return cur;
  }
  if (s[ind] >= '0' && s[ind] <= '9') {
    int oldInd = ind;
    while (ind < sz(s) && isdigit(s[ind]))
      ind++;
    return new Node(atoi(s.substr(oldInd, ind - oldInd).c_str()));
  }
  return nullptr;
}

bool comp(Node* l, Node* r) {
  if (l->value != -1 && r->value != -1) {
    return l->value < r->value;
  }
  if (l->value != -1) {
    return comp(new Node({new Node(l->value)}), r);
  }
  if (r->value != -1) {
    return comp(l, new Node({new Node(r->value)}));
  }
  int ls = sz(l->children), rs = sz(r->children);
  forn (i, min(ls, rs)) {
    if (comp(l->children[i], r->children[i]))
      return 1;
    if (comp(r->children[i], l->children[i]))
      return 0;
  }
  return ls < rs;
}

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
  freopen("out", "w", stdout);
#endif
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  
  string s, t;
  int it = 0, ans = 0;
  while (getline(cin, s)) {
    if (s.empty()) {
      continue;
    }
    it++;
    getline(cin, t);
    int indS = 0, indT = 0;
    ans += it * (comp(parse(s, indS), parse(t, indT)));
  }
  cout << ans << "\n";
  
  return 0;
}
