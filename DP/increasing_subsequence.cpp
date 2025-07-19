#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  ll n;
  cin >> n;

  vector<ll> a(n);
  for (int i = 0; i < n; i++)
  {
    cin >> a[i];
  }

  vector<int> sorted;

  for (int i = 0; i < n; i++)
  {
    auto it = lower_bound(begin(sorted), end(sorted), a[i]);

    if (it == sorted.end())
    {
      sorted.push_back(a[i]);
    }
    else
    {
      *it = a[i];
    }
  }

  cout << sorted.size() << endl;
}