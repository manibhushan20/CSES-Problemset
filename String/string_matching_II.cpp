#include <bits/stdc++.h>
using namespace std;

vector<int> z_function(const string &s)
{
  int n = s.size();
  vector<int> z(n);

  int l = 0, r = 0; // [l, r] is current Z-box
  for (int i = 1; i < n; i++)
  {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);

    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      z[i]++;

    if (i + z[i] - 1 > r)
    {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string text, pattern;
  cin >> text >> pattern;

  string s = pattern + "#" + text;
  vector<int> z = z_function(s);

  int m = pattern.size();
  int count = 0;

  for (int i = m + 1; i < (int)s.size(); i++)
  {
    if (z[i] == m)
      count++;
  }

  cout << count << "\n";
  return 0;
}