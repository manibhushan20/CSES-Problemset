#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  int t;
  cin >> t;

  while (t--)
  {
    int n, k;
    std::cin >> n >> k;

    if (k >= 6)
      k = k % 6 + 6;
    // reduce k, because array stabilizes within 6 steps

    std::vector<int> a(n);
    for (int &x : a)
      std::cin >> x;

    // Perform operations k times
    for (; k--;)
    {
      int mex = 0;
      std::vector<int> cnt(n + 1);

      // count frequency of elements
      for (int x : a)
        ++cnt[x];

      // find mex (smallest number missing from array)
      // for (; cnt[mex]; ++mex)
      //   ;

      while (cnt[mex])
      {
        ++mex;
      }

      // update each element:
      // - if x >= mex OR appears multiple times → becomes mex
      // - else it remains the same
      for (int &x : a)
        x = (x >= mex || cnt[x] > 1 ? mex : x);
    }

    // final sum
    ll ans = 0;
    for (int x : a)
      ans += x;
    std::cout << ans << '\n';
  }
}