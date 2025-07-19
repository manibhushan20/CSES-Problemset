#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  vector<vector<ll>> edges;

  // Add edges from the input
  for (int i = 0; i < m; i++)
  {
    ll u, v, c;
    cin >> u >> v >> c;
    edges.push_back({u, v, c});
  }

  // Add zero-weight edges from super source (0) to all other vertices
  for (int i = 1; i <= n; i++)
  {
    edges.push_back({0, i, 0});
  }

  vector<ll> dist(n + 1, LLONG_MAX);
  dist[0] = 0; // Super source
  vector<int> parent(n + 1, -1);

  int x = -1;
  // Relax all edges (n+1) times (since we now have n+1 vertices)
  for (int i = 0; i <= n + 1; i++)
  {
    x = -1;
    for (auto &edge : edges)
    {
      ll u = edge[0], v = edge[1], c = edge[2];
      if (dist[u] != LLONG_MAX && dist[v] > dist[u] + c)
      {
        dist[v] = dist[u] + c;
        parent[v] = u;
        x = v;
      }
    }
  }

  if (x == -1)
  {
    cout << "NO" << endl;
  }
  else
  {
    cout << "YES" << endl;

    // Trace back from x to find a vertex in the cycle
    for (int i = 0; i <= n; i++)
    {
      x = parent[x];
    }

    // Reconstruct the cycle
    vector<int> cycle;
    int current = x;
    while (true)
    {
      cycle.push_back(current);
      if (current == x && cycle.size() > 1)
      {
        break;
      }
      current = parent[current];
    }

    reverse(cycle.begin(), cycle.end());
    for (auto num : cycle)
    {
      cout << num << " ";
    }
    cout << endl;
  }

  return 0;
}