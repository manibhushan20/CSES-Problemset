#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;

int main()
{
  int n, x;
  cin >> n >> x;
  vector<int> coins(n);
  for (int i = 0; i < n; i++)
    cin >> coins[i];

  sort(begin(coins), end(coins));
  vector<int> dp(x + 1, 0);
  dp[0] = 1;

  for (int amt = 1; amt <= x; amt++)
  {
    for (int coin : coins)
    {
      if (amt - coin >= 0)
      {
        dp[amt] = (dp[amt] + dp[amt - coin]) % mod;
      }
    }
  }

  cout << dp[x] << endl;
}
