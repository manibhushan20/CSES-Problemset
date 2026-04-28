#include <bits/stdc++.h>
using namespace std;

int n, m;
unordered_map<int, vector<int>> adj;
vector<int> parent;
vector<bool> vis;
int startNode = -1, endNode = -1;

bool dfs(int u, int p)
{
  vis[u] = true;
  for (int v : adj[u])
  {
    if (v == p)
      continue; // ignore edge back to parent

    if (vis[v])
    {
      startNode = v;
      endNode = u;
      return true; // cycle found
    }

    parent[v] = u;
    if (dfs(v, u))
      return true;
  }
  return false;
}

int main()
{
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vis.assign(n + 1, false);
  parent.assign(n + 1, -1);

  bool hasCycle = false;
  for (int i = 1; i <= n; i++)
  {
    if (!vis[i] && dfs(i, -1))
    {
      hasCycle = true;
      break;
    }
  }

  if (!hasCycle)
  {
    cout << "IMPOSSIBLE\n";
  }
  else
  {
    vector<int> cycle;
    cycle.push_back(startNode);
    for (int v = endNode; v != startNode; v = parent[v])
      cycle.push_back(v);
    cycle.push_back(startNode);
    reverse(cycle.begin(), cycle.end());

    cout << cycle.size() << "\n";
    for (int x : cycle)
      cout << x << " ";
    cout << "\n";
  }
}
