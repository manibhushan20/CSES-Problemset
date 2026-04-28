#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int solve(vector<int> &arr, int prev, int idx, int n, vector<vector<int>> &dp)
{
  if (idx >= n)
    return 0;

  if (dp[prev + 1][idx] != -1)
    return dp[prev + 1][idx];

  int skip = solve(arr, prev, idx + 1, n, dp);
  int take = 0;
  if (prev == -1 || arr[idx] > arr[prev])

  {
    take = 1 + solve(arr, idx, idx + 1, n, dp);
  }

  return dp[prev + 1][idx] = max(take, skip);
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int n;
  cin >> n;

  vector<int> arr(n);
  for (int i = 0; i < n; i++)
    cin >> arr[i];

  vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

  cout << solve(arr, -1, 0, n, dp) << endl;

  return 0;
}
