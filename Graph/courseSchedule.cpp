#include <bits/stdc++.h>
using namespace std;

bool hasCycle(vector<int> adj[], int u, vector<bool> &vis, vector<bool> &inRecursion)
{
  vis[u] = true;
  inRecursion[u] = true;
  for (int v : adj[u])
  {
    if (inRecursion[v]) // Cycle detected
      return true;
    if (!vis[v] && hasCycle(adj, v, vis, inRecursion))
      return true;
  }
  inRecursion[u] = false;
  return false;
}

int main()
{
  int n, m;
  cin >> n >> m;
  vector<int> adj[n + 1];
  vector<int> inDegree(n + 1, 0);

  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    inDegree[v]++;
  }

  // Check for cycles
  vector<bool> vis(n + 1, false);
  vector<bool> inRecursion(n + 1, false);
  bool cycleFound = false;
  for (int i = 1; i <= n; i++)
  {
    if (!vis[i] && hasCycle(adj, i, vis, inRecursion))
    {
      cycleFound = true;
      break;
    }
  }

  if (cycleFound)
  {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }

  // Perform topological sort using Kahn's algorithm
  queue<int> q;
  for (int i = 1; i <= n; i++)
  {
    if (inDegree[i] == 0)
      q.push(i);
  }

  vector<int> topoOrder;
  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    topoOrder.push_back(u);
    for (int v : adj[u])
    {
      inDegree[v]--;
      if (inDegree[v] == 0)
        q.push(v);
    }
  }

  // Output the topological order
  for (int node : topoOrder)
    cout << node << " ";
  cout << endl;

  return 0;
}