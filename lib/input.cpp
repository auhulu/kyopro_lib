#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long, long long> P;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define agewari(a, b) ((ll)a + ((ll)b - 1)) / b
const int MOD = 1000000007;
const long long INF = 1LL << 60;

int main() {
  //サイズが定まってない標準入力の受け取り方
  vector<string> S;
  while (1) {
    string s;
    cin >> s;
    if (cin.eof()) break;
    S.push_back(s);
  }
  rep(i, S.size()) { cout << S[i] << endl; }

  //行の受け取り方
  string s;
  getline(cin, s);
  cout << s << endl;
}