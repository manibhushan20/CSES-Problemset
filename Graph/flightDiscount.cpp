#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> dijkstra(const vector<vector<pair<ll, ll>>> &adj, ll start, ll n)
{
  vector<ll> dist(n + 1, LLONG_MAX);
  dist[start] = 0;

  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
  pq.push({0, start});

  while (!pq.empty())
  {
    auto it = pq.top();
    ll d = it.first;
    ll u = it.second;
    pq.pop();

    if (d > dist[u])
      continue;

    for (auto it : adj[u])
    {
      ll v = it.first;
      ll c = it.second;
      if (dist[u] + c < dist[v])
      {
        dist[v] = dist[u] + c;
        pq.push({dist[v], v});
      }
    }
  }

  return dist;
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  vector<vector<pair<ll, ll>>> adj(n + 1);
  vector<vector<pair<ll, ll>>> rev_adj(n + 1);
  for (int i = 0; i < m; i++)
  {
    ll u, v, c;
    cin >> u >> v >> c;
    adj[u].push_back({v, c});
    rev_adj[v].push_back({u, c});
  }

  vector<ll> start = dijkstra(adj, 1, n);
  vector<ll> end = dijkstra(rev_adj, n, n);

  ll ans = LLONG_MAX;
  for (int i = 1; i <= n; i++)
  {
    for (auto it : adj[i])
    {
      ll v = it.first;
      ll c = it.second;

      if (start[i] == LLONG_MAX || end[v] == LLONG_MAX)
        continue;
      // Calculate the total cost considering the discount
      ll total_cost = start[i] + end[v] + c / 2;
      ans = min(ans, total_cost);
    }
  }

  if (ans == LLONG_MAX)
  {
    cout << -1 << endl;
  }
  else
  {
    cout << ans << endl;
  }

  return 0;
}