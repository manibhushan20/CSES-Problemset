#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int dp[5001][5001];

int solve(const string &s, const string &t, int i, int j)
{
  if (i == s.length() && j == t.length())
    return 0;
  if (i == s.length())
    return t.length() - j; // Insert remaining characters
  if (j == t.length())
    return s.length() - i; // Delete remaining characters

  if (dp[i][j] != -1)
    return dp[i][j];

  int cost = 0;
  if (s[i] == t[j])
  {
    cost = solve(s, t, i + 1, j + 1); // No cost, move to next
  }
  else
  {
    int insert = solve(s, t, i, j + 1);      // Insert t[j] into s
    int del = solve(s, t, i + 1, j);         // Delete s[i]
    int replace = solve(s, t, i + 1, j + 1); // Replace s[i] with t[j]
    cost = 1 + min({insert, del, replace});
  }

  return dp[i][j] = cost;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  string s, t;
  cin >> s >> t;

  memset(dp, -1, sizeof(dp));
  cout << solve(s, t, 0, 0);

  return 0;
}