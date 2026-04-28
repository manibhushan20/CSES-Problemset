#include <bits/stdc++.h>
using namespace std;
using ll = unsigned long long;

int main()
{
  int t;
  cin >> t;

  // chocola->1, vanilla->2, chocola=x

  while (t--)
  {
    ll k, x;
    cin >> k >> x;

    ll init = pow(2, k);

    if (x == init)
    {
      cout << 0 << endl;
      cout << endl;
      continue;
    }

    ll ch = x;
    ll vi = (init * 2) - x;

    vector<int> v;
    while (ch != init && vi != init)
    {
      if (ch > vi)
      {
        ll diff = vi;
        ch -= diff;
        vi += diff;
        v.push_back(2);
      }
      else if (vi > ch)
      {
        ll diff = ch;
        ch += diff;
        vi -= diff;
        v.push_back(1);
      }
      else
      {
        break;
      }
    }

    cout << v.size() << endl;
    reverse(begin(v), end(v));
    for (int ele : v)
    {
      cout << ele << " ";
    }
    cout << endl;
  }
}