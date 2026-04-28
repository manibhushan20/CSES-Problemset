#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int solve(int n, int x, vector<int> &coins, vector<int> &dp)
{
  if (x == 0)
    return 1;
  if (dp[x] != -1)
    return dp[x];

  int res = 0;
  for (int i = 0; i < n; i++)
  {
    if (x >= coins[i])
      res = (res + solve(n, x - coins[i], coins, dp)) % mod;
    else
      break;
  }
  return dp[x] = res;
}

int main()
{
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; i++)
    cin >> coins[i];

  sort(begin(coins), end(coins));
  vector<int> dp(x + 1, -1);

  cout << solve(n, x, coins, dp) << endl;
}
