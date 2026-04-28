#include <bits/stdc++.h>
using namespace std;

int main()
{
  int t;
  cin >> t;

  while (t--)
  {
    long long n;
    cin >> n;

    string s;
    cin >> s;

    int noz = 0;
    int noo = 0;
    for (int i = 0; i < n; i++)
    {
      if (s[i] == '0')
        noz++;
      else
        noo++;
    }

    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
      if ((i < noz) && (s[i] == '1'))
        cnt++;
      else if (i >= noz && s[i] == '0')
        cnt++;
    }

    cout << cnt / 2 << endl;
  }
}