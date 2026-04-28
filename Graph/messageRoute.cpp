#include <bits/stdc++.h>
using namespace std;

int main()
{
  int n, m;
  cin >> n >> m;

  vector<vector<int>> graph(n + 1);
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  vector<int> dist(n + 1, INT_MAX), path(n + 1, -1);
  queue<int> q;
  q.push(1);
  dist[1] = 0;

  while (!q.empty())
  {
    int node = q.front();
    q.pop();

    for (int v : graph[node])
    {
      if (dist[v] == INT_MAX)
      { // not visited yet
        dist[v] = dist[node] + 1;
        path[v] = node;
        q.push(v);
      }
    }
  }

  if (dist[n] == INT_MAX)
  {
    cout << "IMPOSSIBLE" << endl;
    return 0;
  }

  vector<int> ans;
  for (int cur = n; cur != -1; cur = path[cur])
    ans.push_back(cur);

  reverse(ans.begin(), ans.end());

  cout << ans.size() << endl;
  for (int x : ans)
    cout << x << " ";
  cout << endl;
}
