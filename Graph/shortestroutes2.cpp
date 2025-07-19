#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m, q;
  cin >> n >> m >> q;

  vector<vector<ll>> adj(n + 1, vector<ll>(n + 1, LLONG_MAX));
  for (int i = 1; i <= n; i++)
  {
    adj[i][i] = 0; // Distance to self is zero
  }

  for (int i = 0; i < m; i++)
  {
    ll u, v, c;
    cin >> u >> v >> c;
    adj[u][v] = min(adj[u][v], c);
    adj[v][u] = min(adj[v][u], c); // undirected graph
  }

  for (int k = 1; k <= n; k++)
  {
    for (int u = 1; u <= n; u++)
    {
      for (int v = 1; v <= n; v++)
      {
        if (adj[u][k] != LLONG_MAX && adj[k][v] != LLONG_MAX)
        {
          adj[u][v] = min(adj[u][v], adj[u][k] + adj[k][v]);
        }
      }
    }
  }

  while (q--)
  {
    int u, v;
    cin >> u >> v;

    if (adj[u][v] == LLONG_MAX)
    {
      cout << -1 << endl;
    }
    else
    {
      cout << adj[u][v] << endl;
    }
  }

  return 0;
}