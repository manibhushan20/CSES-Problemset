#include <bits/stdc++.h>
using namespace std;

bool dfs(vector<vector<int>> &adj, int u, vector<bool> &vis, vector<bool> &inRecursion, vector<int> &parent, int &cycleStart, int &cycleEnd)
{
  vis[u] = true;
  inRecursion[u] = true;

  for (auto v : adj[u])
  {
    if (inRecursion[v])
    {
      cycleStart = v;
      cycleEnd = u;
      return true;
    }
    if (vis[v])
      continue;

    parent[v] = u;
    if (dfs(adj, v, vis, inRecursion, parent, cycleStart, cycleEnd))
      return true;
  }

  inRecursion[u] = false;
  return false;
}

int main()
{
  int n, m;
  cin >> n >> m;
  vector<vector<int>> adj(n + 1);

  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
  }

  vector<int> parent(n + 1, -1);
  vector<bool> vis(n + 1, false);
  vector<bool> inRecursion(n + 1, false);
  int cycleStart = -1, cycleEnd = -1;

  for (int i = 1; i <= n; i++)
  {
    if (!vis[i] && dfs(adj, i, vis, inRecursion, parent, cycleStart, cycleEnd))
      break;
  }

  if (cycleStart == -1)
  {
    cout << "IMPOSSIBLE" << endl;
  }
  else
  {
    vector<int> cycle;
    cycle.push_back(cycleStart);

    for (int current = cycleEnd; current != cycleStart; current = parent[current])
      cycle.push_back(current);

    cycle.push_back(cycleStart);

    reverse(cycle.begin(), cycle.end());
    
    cout << cycle.size() << endl;
    for (int num : cycle)
      cout << num << " ";
    cout << endl;
  }

  return 0;
}