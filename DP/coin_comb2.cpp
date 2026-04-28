#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n, x;
  cin >> n >> x;

  const int MOD = 1e9 + 7;

  vector<int> coins(n);
  for (int i = 0; i < n; i++)
    cin >> coins[i];

  vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
  for (int i = 0; i <= n; i++)
  {
    dp[i][0] = 1;
  }

  for (int i = n - 1; i >= 0; i--)
  {
    for (int sum = 1; sum <= x; sum++)
    {
      int skip = dp[i + 1][sum];
      int take = 0;
      if (coins[i] <= sum)
        take = dp[i][sum - coins[i]];

      dp[i][sum] = (skip + take) % MOD;
    }
  }

  cout << dp[0][x] << endl;

  return 0;
}
