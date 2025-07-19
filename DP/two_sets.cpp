#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll MOD = 1e9 + 7;

ll modinv(ll x)
{
  // Fermat's little theorem, since MOD is prime:
  // x^(MOD-2) % MOD
  ll res = 1, p = MOD - 2;
  while (p)
  {
    if (p & 1)
      res = (res * x) % MOD;
    x = (x * x) % MOD;
    p >>= 1;
  }
  return res;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n;
  cin >> n;
  ll total = n * (n + 1) / 2;
  // If total sum is odd, you can't split into two equal subsets.
  if (total & 1)
  {
    cout << 0 << "\n";
    return 0;
  }
  ll target = total / 2;

  // dp[s] = # ways to pick a subset of {1..i} summing to s
  vector<ll> dp(target + 1, 0);
  dp[0] = 1;

  // Classic 0/1‐knapsack roll‑backwards to avoid overwriting
  for (ll i = 1; i <= n; i++)
  {
    for (ll s = target; s >= i; s--)
    {
      dp[s] = (dp[s] + dp[s - i]) % MOD;
    }
  }

  // Each valid subset is paired with its complement,
  // so we've counted each partition twice.
  // Divide by 2 via multiplying the modular inverse.
  ll inv2 = modinv(2);
  ll ans = dp[target] * inv2 % MOD;
  cout << ans << "\n";
  return 0;
}
