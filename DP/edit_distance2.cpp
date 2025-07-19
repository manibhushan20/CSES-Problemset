#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  string s, t;
  cin >> s >> t;

  int n = s.size(), m = t.size();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));

  // Base cases
  for (int i = 0; i <= n; ++i)
    dp[i][m] = n - i; // Need to delete remaining characters in s
  for (int j = 0; j <= m; ++j)
    dp[n][j] = m - j; // Need to insert remaining characters in t

  for (int i = n - 1; i >= 0; --i)
  {
    for (int j = m - 1; j >= 0; --j)
    {
      if (s[i] == t[j])
      {
        dp[i][j] = dp[i + 1][j + 1];
      }
      else
      {
        dp[i][j] = 1 + min({dp[i + 1][j],       // Delete from s
                            dp[i][j + 1],       // Insert into s
                            dp[i + 1][j + 1]}); // Replace
      }
    }
  }

  cout << dp[0][0];

  return 0;
}