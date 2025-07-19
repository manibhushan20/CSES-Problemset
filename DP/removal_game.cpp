#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// sentinel for “not yet computed”
static const ll UNDEF = LLONG_MIN;

int n;
vector<ll> a;
vector<vector<ll>> dp;

// returns the net score difference (current player minus opponent) on subarray [i..j]
ll solve(int i, int j)
{
  if (dp[i][j] != UNDEF)
    return dp[i][j];
  if (i == j)
    return dp[i][j] = a[i];

  // if we take a[i], net = a[i] - D(i+1,j)
  ll pickLeft = a[i] - solve(i + 1, j);
  // if we take a[j], net = a[j] - D(i,j-1)
  ll pickRight = a[j] - solve(i, j - 1);

  return dp[i][j] = max(pickLeft, pickRight);
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  a.resize(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  // precompute total sum
  ll total = accumulate(a.begin(), a.end(), 0LL);

  // init memo table to UNDEF
  dp.assign(n, vector<ll>(n, UNDEF));

  // get the difference on the full array
  ll diff = solve(0, n - 1);

  // first player's score = (sum + diff) / 2
  ll firstScore = (total + diff) / 2;
  cout << firstScore << "\n";
  return 0;
}
