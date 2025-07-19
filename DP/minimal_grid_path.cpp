#include <bits/stdc++.h>

using namespace std;

int main()
{
  int n;
  cin >> n;
  vector<vector<char>> grid(n, vector<char>(n));

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> grid[i][j];
    }
  }

  vector<vector<int>> dp(n, vector<int>(n, 0));

  for (int i = n - 1; i > 0; i--)
  {
    for (int j = 0; j < n; j++)
    {
      if (grid[i - 1][j] == grid[i][j + 1])
      {
        dp[i][j] = int(grid[i - 1][j]) + min(i + 1 < n ? dp[i + 1][j] : INT_MAX, j - 1 > 0 ? dp[i][j - 1] : INT_MAX);
      }
      else if (grid[i - 1][j] < grid[i][j + 1])
      {
        dp[i][j] = int(grid[i - 1][j]) + min(i + 1 < n ? dp[i + 1][j] : INT_MAX, j - 1 > 0 ? dp[i][j - 1] : INT_MAX);
      }
      else
      {
        dp[i][j] = int(grid[i][j - 1]) + min(i + 1 < n ? dp[i + 1][j] : INT_MAX, j - 1 > 0 ? dp[i][j - 1] : INT_MAX);
      }
    }
  }

  string res = "";
  res += grid[0][n - 1];

  int i = 0;
  int j = n;

  while (i < n - 1 && j > 0)
  {
    if (dp[i + 1][j] < dp[i][j - 1])
    {
      res += grid[i + 1][j];
      i++;
    }
    else
    {
      res += grid[i][j - 1];
      j--;
    }
  }

  res += grid[n - 1][0];

  reverse(begin(res), end(res));

  cout << res << endl;
}