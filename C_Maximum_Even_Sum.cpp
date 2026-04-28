#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  int t;
  cin >> t;

  while (t--)
  {
    ll a, b;
    cin >> a >> b;

    if (b & 1)
    {
      if (a & 1)
      {
        cout << a * b + 1;
      }
      else
      {
        cout << -1;
      }
    }
    else
    {
      if ((a & 1) == 0)
      {
        cout << max(a * (b / 2) + 2, a + b);
      }
      else
      {
        if ((b / 2) & 1)
        {
          cout << -1;
        }
        else
        {
          cout << a * (b / 2) + 2;
        }
      }
    }

    cout << endl;
  }
}