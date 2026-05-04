#include <bits/stdc++.h>
using namespace std;

int n, m;

vector<int> LPS(string &t)
{
  vector<int> lps(m, 0);
  int length = 0, index = 1;

  while (index < m)
  {
    if (t[length] == t[index])
    {
      length++;
      lps[index] = length;
      index++;
    }
    else
    {
      if (length != 0)
      {
        length = lps[length - 1];
      }
      else
      {
        lps[index] = 0;
        index++;
      }
    }
  }

  return lps;
}

int main()
{
  string s, t;
  cin >> s >> t;

  n = s.length(), m = t.length();

  vector<int> lps = LPS(t);

  int res = 0;

  int i = 0, j = 0;
  while (i < n)
  {
    if (s[i] == t[j])
    {
      i++;
      j++;

      if (j == m)
      {
        res++;
        j = lps[j - 1];
      }
    }
    else
    {
      if (j != 0)
        j = lps[j - 1];
      else
        i++;
    }
  }

  cout << res;
}