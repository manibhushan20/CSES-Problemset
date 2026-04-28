#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  int t;
  cin >> t;

  while (t--)
  {
    long long n, m;
    cin >> n >> m;

    ll a[n];
    for (int i = 0; i < n; i++)
      cin >> a[i];

    sort(a, a + n);

    ll res = 0;

    for (int i = n - 1; i >= 0; i--)
    {
      res += (a[i] * m);
      m--;
      if (m == 0)
        break;
    }

    cout << res << endl;
  }
}