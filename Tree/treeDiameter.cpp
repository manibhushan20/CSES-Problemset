#include <bits/stdc++.h>
using namespace std;

int res = 0;

int solve(unordered_map<int, vector<int>> &adj, int node, int parent)
{

  int maxi = 0, smaxi = 0;

  for (int adjNode : adj[node])
  {
    if (adjNode == parent)
      continue;
    int len = solve(adj, adjNode, node);
    if (len > maxi)
    {
      smaxi = maxi;
      maxi = len;
    }
    else if (len > smaxi)
    {
      smaxi = len;
    }
  }

  res = max(res, 1 + maxi + smaxi);

  return 1 + max(maxi, smaxi);
}

int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n))
    return 0;

  unordered_map<int, vector<int>> adj;

  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  solve(adj, 1, 0);

  cout << res - 1;

  return 0;
}