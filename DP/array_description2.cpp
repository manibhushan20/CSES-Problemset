#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int MOD = 1e9 + 7;

bool valid(int x, int m)
{
  return x >= 1 && x <= m;
}

int main()
{
  ll n, m;
  cin >> n >> m;

  vector<ll> a(n);
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }

  vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));

  for (int k = 1; k <= m; k++)
  {
    if (a[0] == k || a[0] == 0)
      dp[1][k] = 1;
  }

  for (int len = 2; len <= n; len++)
  {
    for (int k = 1; k <= m; k++)
    {
      if (a[len - 1] != 0 && a[len - 1] != k)
      {
        dp[len][k] = 0;
        continue;
      }

      for (int prev = k - 1; prev <= k + 1; prev++)
      {
        if (!valid(prev, m))
          continue;

        dp[len][k] = (dp[len][k] + dp[len-1][prev]) % MOD;
      }
    }
  }

  ll res = 0;
  for (int k = 1; k <= m; k++)
  {
    res = (res + dp[n][k]) % MOD;
  }

  cout << res;

  return 0;
}