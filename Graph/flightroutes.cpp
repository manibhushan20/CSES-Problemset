#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
  ll n, m, k;
  cin >> n >> m >> k;

  vector<pair<int, ll>> adj[n + 1];

  for (int i = 0; i < m; i++)
  {
    ll u, v, c;
    cin >> u >> v >> c;
    adj[u].push_back({v, c});
  }

  // Each vertex will have a list of up to k smallest distances
  vector<ll> dist[n + 1];

  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
  pq.push({0, 1});

  while (!pq.empty())
  {
    auto it = pq.top();
    pq.pop();

    ll current_dist = it.first;
    ll u = it.second;

    // If the current distance is larger than the k-th distance for u, skip
    if (dist[u].size() >= k)
    {
      continue;
    }

    dist[u].push_back(current_dist);

    for (auto &edge : adj[u])
    {
      ll v = edge.first;
      ll cost = edge.second;
      ll new_dist = current_dist + cost;
      pq.push({new_dist, v});
    }
  }

  // Output the k shortest paths to vertex n
  for (int i = 0; i < k; i++)
  {
    if (i < dist[n].size())
    {
      cout << dist[n][i] << " ";
    }
    else
    {
      cout << "-1 "; // In case there are less than k paths
    }
  }
  cout << endl;

  return 0;
}