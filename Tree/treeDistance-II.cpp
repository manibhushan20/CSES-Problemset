#include <bits/stdc++.h>
using namespace std;

void solve(unordered_map<int, vector<int>> &adj, int node, int parent, int d, int &res, int &maxDist)
{
  if (d > maxDist)
  {
    maxDist = d;
    res = node;
  }

  for (int adjNode : adj[node])
  {
    if (adjNode == parent)
      continue;
    solve(adj, adjNode, node, d + 1, res, maxDist);
  }
}

void distanceFind(unordered_map<int, vector<int>> &adj, int node, int parent, int d, vector<int> &dist)
{
  dist[node] = d;

  for (int adjNode : adj[node])
  {
    if (adjNode == parent)
      continue;
    distanceFind(adj, adjNode, node, d + 1, dist);
  }
}

int main()
{

  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n))
    return 0;

  if (n == 1)
  {
    cout << 0;
    return 0;
  }

  unordered_map<int, vector<int>> adj;

  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  int A, B;
  int maxDist = 0;
  solve(adj, 1, 0, 0, A, maxDist);
  maxDist = 0;
  solve(adj, A, 0, 0, B, maxDist);

  vector<int> distA(n + 1, 0);
  vector<int> distB(n + 1, 0);

  distanceFind(adj, A, 0, 0, distA);
  distanceFind(adj, B, 0, 0, distB);

  for (int i = 1; i <= n; i++)
  {
    cout << max(distA[i], distB[i]) << " ";
  }

  return 0;
}