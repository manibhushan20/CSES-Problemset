#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  int t;
  cin >> t;

  while (t--)
  {
    int n;
    cin >> n;

    ll b[n];

    for (int i = 0; i < n; i++)
      cin >> b[i];

    map<int, int> mp;
    ll sum = 0;
    ll reqSum = 0;
    for (int i = 0; i < n; i++)
    {
      if (!mp.count(b[i]))
      {
        sum += b[i];
      }
      mp[b[i]]++;
    }

    bool flag = true;
    ll total = 0;

    int curr = n;
    map<int, vector<int>> mpp;

    for (auto &it : mp)
    {
      int ele = it.first;
      int freq = it.second;

      if (freq % ele != 0)
      {
        flag = false;
      }
      int num = freq / ele;
      total += ele * num;
      while (num--)
      {
        mpp[ele].push_back(curr);
        curr--;
      }
    }

    if (!flag || total != n)
    {
      cout << -1 << endl;
      continue;
    }

    if (sum == n)
    {
      for (int i = 0; i < n; i++)
        cout << b[i] << " ";
      cout << endl;
      continue;
    }

    vector<int> res(n);
    map<int, int> used;

    for (int i = 0; i < n; i++)
    {
      res[i] = mpp[b[i]].back();
      used[b[i]]++;
      if (b[i] == used[b[i]])
      {
        mpp[b[i]].pop_back();
        used[b[i]] = 0;
      }
    }

    for (int i = 0; i < n; i++)
    {
      cout<< res[i] << " ";
    }

    cout << endl;
  }
}