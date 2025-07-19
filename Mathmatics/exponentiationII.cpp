#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll findExponentiation(ll base, ll exp, ll mod)
{
  ll res = 1;
  while (exp)
  {
    if (exp & 1)
    {
      res = (res * base) % mod;
    }

    base = (base * base) % mod;
    exp >>= 1;
  }

  return res;
}

int main()
{
  ll n;
  cin >> n;

  ll mod = 1e9 + 7;

  for (ll i = 0; i < n; i++)
  {
    ll a, b, c;
    cin >> a >> b >> c;

    ll exp = findExponentiation(b, c, mod - 1);
    ll res = findExponentiation(a, exp, mod);

    cout << res << endl;
  }

  return 0;
}