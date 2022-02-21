#include <bits/stdc++.h>
using namespace std;
typedef ll ll;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define agewari(a, b) ((ll)a + ((ll)b - 1)) / b
const ll MOD = 1000000007;
const ll INF = 1LL << 60;

//グラフ(重みなし)
using Graph = vector<vector<ll>>;  // グラフ型

//グラフ(重み付き)
struct Edge {
  ll to;      // 辺の行き先
  ll weight;  // 辺の重み
  Edge(ll t, ll w) : to(t), weight(w) {}
};
using Graph = vector<vector<Edge>>;

// DFS
vector<vector<ll>> G;  // mainでresize必要
vector<bool> seen;
void dfs(ll v) {
  // 行きがけ
  seen[v] = true;
  for (auto nv : G[v]) {
    if (seen[nv]) continue;
    dfs(nv);
  }
  // 帰りがけ
}

//組み合わせの数nCrを計算
ll nCr(ll n, ll r) {
  ll num = 1;
  for (ll i = 1; i <= r; i++) {
    num = num * (n - i + 1) / i;
  }
  return num;
}

// popcount
ll popcount(ll n) { return __builtin_popcount(n); }

//因数分解→map<素因数,それぞれいくつか>の形に格納
map<ll, ll> prime;  //素因数分解でそれぞれの素数がいくつ出てきたかを保存するmap

// O(√n)
//整列済み(mapはkeyで自動で整列される)
void prime_factorize(ll n) {
  if (n <= 1) return;
  ll l = sqrt(n);
  for (ll i = 2; i <= l; i++) {
    if (n % i == 0) {
      prime_factorize(i);
      prime_factorize(ll(n / i));
      return;
    }
  }
  // mapでは存在しないkeyの場合も自動で構築される
  prime[n]++;
  return;
}

//エラトステネスのふるい
// O(nloglogn)
vector<bool> IsPrime;

void sieve(size_t max) {
  if (max + 1 > IsPrime.size()) {  // resizeで要素数が減らないように
    IsPrime.resize(max + 1, true);  // IsPrimeに必要な要素数を確保
  }
  IsPrime[0] = false;  // 0は素数ではない
  IsPrime[1] = false;  // 1は素数ではない

  for (size_t i = 2; i * i <= max; ++i)      // 0からsqrt(max)まで調べる
    if (IsPrime[i])                          // iが素数ならば
      for (size_t j = 2; i * j <= max; ++j)  // (max以下の)iの倍数は
        IsPrime[i * j] = false;              // 素数ではない
}

// a^n mod を高速に計算する(O(log n))
ll modpow(ll a, ll n, ll mod) {
  ll res = 1;
  while (n > 0) {
    if (n & 1) res = res * a % mod;
    a = a * a % mod;
    n >>= 1;
  }
  return res;
}

//けんちょん式 Union-Find
struct UnionFind {
  vector<ll> par;

  UnionFind(ll n) : par(n, -1) {}

  ll root(ll x) {
    if (par[x] < 0)
      return x;
    else
      return par[x] = root(par[x]);
  }

  bool issame(ll x, ll y) { return root(x) == root(y); }

  bool merge(ll x, ll y) {
    x = root(x);
    y = root(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }

  ll size(ll x) { return -par[root(x)]; }
};

//ダイクストラ法
vector<ll> dijkstra(ll n, Graph G, ll s) {
  vector<ll> d(n, LLONG_MAX / 10);
  d[s] = 0;
  priority_queue<pair<ll, ll>> que;
  que.push(make_pair(0ll, s));
  while (!que.empty()) {
    auto p = que.top();
    que.pop();
    ll u = p.second;
    ll dist = -p.first;
    if (dist > d[u]) continue;
    for (Edge e : G[u]) {
      if (d[e.to] > d[u] + e.weight) {
        d[e.to] = d[u] + e.weight;
        que.push(make_pair(-d[e.to], e.to));
      }
    }
  }
  return d;
}

// めぐるしきにぶたん
vector<ll> a = {1, 14, 32, 51, 51, 51, 243, 419, 750, 910};

// index が条件を満たすかどうか
bool isOK(ll index, ll key) {
  if (a[index] >= key)
    return true;
  else
    return false;
}

// 汎用的な二分探索のテンプレ
ll binary_search(ll key) {
  ll ng = -1;  //「index = 0」が条件を満たすこともあるので、初期値は -1
  ll ok = (ll)a.size();  //
  /* ok と ng のどちらが大きいかわからないことを考慮 */
  while (abs(ok - ng) > 1) {
    ll mid = (ok + ng) / 2;

    if (isOK(mid, key))
      ok = mid;
    else
      ng = mid;
  }
  return ok;
}

void main() {
  //割り算切り上げ
  ll a = 17, b = 7;
  cout << (a + (b - 1)) / b << endl;  // 3

  //小数点以下桁数指定
  cout << fixed << setprecision(10) << 1 / 3.0 << endl;

  // pair型vetorの扱い
  vector<pair<ll, ll>> V;  // backで入れるときは初期化しない！
  V.emplace_back(5, 17);
  cout << V[0].first << " " << V[0].second << endl;

  //昇順ソート
  vector<ll> G = {5, 3, 6, 2, 9};
  sort(G.begin(), G.end(), greater<ll>());
  for (auto g : G) cout << g << endl;

  //小さい順priority_queue
  priority_queue<ll, vector<ll>, greater<ll>> que;

  //２次元配列宣言
  vector<vector<ll>> V(a, vector<ll>(b));

  //にぶたん
  // upper_boundはkeyより大きい
  // lower_boundはkey以上
  vector<ll> A = {1, 2, 3, 4, 5, 6};
  auto it = upper_bound(A.begin(), A.end(), 3);
  cout << *it << endl;                //要素を表示
  cout << it - A.begin() << endl;     // indexを表示
  cout << A[it - A.begin()] << endl;  //要素を表示

  //空白文字で分割表示
  string line = "AAA BBB CCC";
  istringstream iss(line);
  string s;
  while (iss >> s) {
    cout << s << endl;
  }

  // bit全探索
  ll n = 10;  //桁数
  for (ll i = 0; i < (1 << n); i++) {
    ll j = 3;
    if (i & (1 << j)) cout << "右からj番目は1" << endl;
  }

  // BFS
  vector<vector<ll>> G(n);
  vector<ll> dist(n, -1);
  queue<ll> que;

  dist[0] = 0;
  que.push(0);
  while (!que.empty()) {
    ll v = que.front();
    que.pop();
    for (ll nv : G[v]) {
      if (dist[nv] != -1) continue;
      dist[nv] = dist[v] + 1;
      que.push(nv);
    }
  }
}