#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rep(i, n) for (int i = 0; i < (int)(n); i++)

int main() {
  // int(文字コード)からcharに
  int Ai = 65;  // Aを示す文字コード
  char Ac = Ai;
  cout << Ac << endl;  // Aが表示

  // int(数字)からcharに
  int Ni = 1;
  char Nc = Ni + '0';
  cout << Nc << endl;  // 1が表示

  // charからint(文字コード)に
  char Ac2 = 'A';
  int Ai2 = Ac2;
  cout << Ai2 << endl;  // Aを示す65が表示

  // char(数字)からintに
  char Nc2 = '1';
  int Ni2 = Nc2 - '0';
  cout << Ni2 << endl;  // 1が表示


  // string(数字)からllに
  string Ns = "001";
  ll Ni3 = stoll(Ns);
  cout << Ni3 << endl;  /// 1が表示

  // llからstringに
  ll Ni4 = 111;
  string Ns2 = to_string(Ni4);
  cout << Ns2 << endl;  /// 111が表示
}