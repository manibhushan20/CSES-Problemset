#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
  ll n, m;
  cin >> n >> m;

  ll a[n], b[m];

  for (int i = 0; i < n; i++)
    cin >> a[i];
  for (int j = 0; j < m; j++)
    cin >> b[j];

  vector<vector<ll>> dp(n + 1, vector<ll>(m + 1, 0));

  for (int i = 1; i <= n; i++)
  {
    for (int j = 1; j <= m; j++)
    {
      if (a[i - 1] == b[j - 1])
      {
        dp[i][j] = 1 + dp[i - 1][j - 1];
      }
      else
      {
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
  }

  vector<int> res;
  int i = n;
  int j = m;

  while (i > 0 && j > 0)
  {
    if (a[i - 1] == b[j - 1])
    {
      res.push_back(a[i - 1]);
      i--;
      j--;
    }
    else
    {
      if (dp[i - 1][j] > dp[i][j - 1])
      {
        i--;
      }
      else
      {
        j--;
      }
    }
  }

  reverse(res.begin(), res.end());
  cout << res.size() << endl;
  for (ll ele : res)
  {
    cout << ele << " ";
  }
}