#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  int t;
  cin >> t;

  while (t--)
  {
    ll n;
    cin >> n;

    ll a[n + 1];
    for (int i = 1; i <= n; i++)
      cin >> a[i];

    ll odd = 0;
    ll even = 0;

    bool flag = true;
    int maxIdx = 0;
    ll maxi = 0;
    int minIdx = 0;
    ll mini = INT_MAX;
    vector<pair<int, int>> evenV;
    vector<pair<int, int>> oddV;

    for (int i = 1; i <= n; i++)
    {
      if (i > 1 && a[i] != a[i - 1])
        flag = false;
      if (i & 1)
      {
        odd += a[i];
        oddV.push_back({a[i], i});
      }
      else
      {
        even += a[i];
        evenV.push_back({a[i], i});
      }
    }

    if (flag)
    {
      cout << n * a[1] + (n - 1) << endl;
      continue;
    }

    sort(begin(oddV), end(oddV));
    int ol = oddV.size();
    int el = evenV.size();
    sort(begin(evenV), end(evenV));

    ll res = max({odd - even, odd - even - oddV[0].first + evenV[el - 1].first + abs(oddV[0].second - evenV[el - 1].second)});
    cout << res << endl;
  }
}