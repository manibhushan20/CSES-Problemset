#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;
  vector<vector<int>> g(n + 1);
  vector<int> in(n + 1, 0);
  while (m--)
  {
    int a, b;
    cin >> a >> b;
    g[a].push_back(b);
    in[b]++;
  }
  // Topological sort (Kahn's Algorithm)
  queue<int> q;
  vector<int> dist(n + 1, INT_MIN), prev(n + 1, -1);
  dist[1] = 1;
  for (int i = 1; i <= n; ++i)
    if (!in[i])
      q.push(i);

  while (!q.empty())
  {
    int u = q.front();
    q.pop();
    for (int v : g[u])
    {
      if (dist[u] + 1 > dist[v])
      {
        dist[v] = dist[u] + 1;
        prev[v] = u;
      }
      if (--in[v] == 0)
        q.push(v);
    }
  }
  if (dist[n] < 1)
  {
    cout << "IMPOSSIBLE\n";
    return 0;
  }
  // Recover path
  vector<int> path;
  for (int v = n; v != -1; v = prev[v])
    path.push_back(v);

  reverse(path.begin(), path.end());

  cout << dist[n] << endl;

  for (int v : path)
    cout << v << " ";

  cout << endl;
}
