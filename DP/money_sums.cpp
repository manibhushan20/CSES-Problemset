#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n;
set<ll> st;
ll dp[101][100001];

ll solve(vector<ll> &a, int idx, ll sum)
{
  if (idx >= n)
  {
    if (sum > 0 && !st.count(sum))
    {
      st.insert(sum);
      return 1;
    }
    return 0;
  }

  if (dp[idx][sum] != -1)
    return dp[idx][sum];

  ll res = 0;

  res += solve(a, idx + 1, sum); // skip res += solve(a, idx + 1, sum + a[idx]); // take

  return dp[idx][sum] = res;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  memset(dp, -1, sizeof(dp));

  cin >> n;

  vector<ll> a(n);

  ll sum = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
    sum += a[i];
  }

  vector<bool> possible(sum + 1, false);
  possible[0] = true;

  for (int i = 0; i < n; i++)
  {
    for (ll val = sum; val >= 0; val--)
    {
      if (val - a[i] >= 0)
        possible[val] = possible[val] | possible[val - a[i]];
    }
  }

  int cnt = 0;
  for (int i = 1; i <= sum; i++)
    if (possible[i])
      cnt++;

  cout << cnt << endl;

  for (int i = 1; i <= sum; i++)
    if (possible[i])
      cout << i << " ";

  return 0;
}