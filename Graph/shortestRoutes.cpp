#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll n, m;
  cin >> n >> m;

  //vector<vector<pair<ll, ll>>> adj(n + 1);
  unordered_map<ll, vector<pair<ll, ll>>>adj;
  for (int i = 0; i < m; i++)
  {
    ll u, v, c;
    cin >> u >> v >> c;
    adj[u].emplace_back(v, c);
  }

  vector<ll> dist(n + 1, LLONG_MAX);
  dist[1] = 0;

  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
  pq.push({0, 1});

  while (!pq.empty())
  {
    auto it = pq.top();
    ll d = it.first, u = it.second;
    pq.pop();

    // Skip if we already found a better path for this node
    if (d > dist[u])
      continue;

    for (auto edge : adj[u])
    {
      ll v = edge.first, c = edge.second;
      if (dist[v] > d + c)
      {
        dist[v] = d + c;
        pq.push({dist[v], v});
      }
    }
  }

  for (int i = 1; i <= n; i++)
  {
    cout << (dist[i] == LLONG_MAX ? -1 : dist[i]) << " ";
  }
  cout << endl;

  return 0;
}