#include <bits/stdc++.h>
using namespace std;
vector<int> bfs(const unordered_map<int, vector<int>>& adj, int start, int n)
{
  vector<int> dist(n + 1, INT_MAX);
  queue<int> q;

  dist[start] = 0;
  q.push(start);

  while (!q.empty())
  {
    int u = q.front();
    q.pop();

    for (int v : adj.at(u))
    {
      if (dist[v] > dist[u] + 1)
      {
        dist[v] = dist[u] + 1;
        q.push(v);
      }
    }
  }

  return dist;
}


int main()
{
  int n, m;
  cin >> n >> m;

  unordered_map<int, vector<int>> adj;
  unordered_map<int, vector<int>> rev_adj;

  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    rev_adj[v].push_back(u);
  }

  int k;
  cin >> k;
  vector<int> monuments(k);
  for (int i = 0; i < k; i++)
  {
    cin >> monuments[i];
  }

  vector<int> forward_path = bfs(adj, 1, n);
  vector<int> reverse_path = bfs(rev_adj, 1, n);

  long long flights = 0;
  for (int i = 0; i < k; i++)
  {
    int monument = monuments[i];
    flights += forward_path[monument] + reverse_path[monument];
  }

  cout << flights << endl;
  return 0;
}