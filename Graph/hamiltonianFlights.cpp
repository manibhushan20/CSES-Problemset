#include <bits/stdc++.h>

using namespace std;
int mod = 1e9 + 7;

int main()
{
  int n, m;
  cin >> n >> m;

  vector<int> adj[n + 1];
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  int res = 0;
  queue<pair<int, int>> q;
  q.push({1, 0});

  while (!q.empty())
  {
    auto it = q.front();
    q.pop();
    int u = it.first;
    int d = it.second;


    if (u == n)
    {
      res = (res + 1) % mod;
      continue;
    }

    for (int v : adj[u])
    {
      q.push({v, d + 1});
    }
  }

  cout << res << endl;
  return 0;
}