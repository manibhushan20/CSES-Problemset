#include <bits/stdc++.h>
using namespace std;
using ll = long long;
long long MOD = 1e9 + 7;

int main()
{
  ll n;
  cin >> n;

  vector<ll> a(n);
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }

  vector<long long> dp(n + 1, 0);
  long long res = n;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      if (a[j] < a[i])
        res = (res + 1) % MOD;
    }
  }

  cout << res << endl;
}