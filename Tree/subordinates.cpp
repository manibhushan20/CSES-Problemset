#include <bits/stdc++.h>
using namespace std;

int solve(int node, unordered_map<int, vector<int>> &adj, vector<int> &dist)
{
  int cnt = 0;
  for (int adjNode : adj[node])
  {
    cnt += solve(adjNode, adj, dist);
  }

  dist[node] = cnt;
  return cnt + 1;
}

int main()
{
  int n;
  cin >> n;

  unordered_map<int, vector<int>> adj;

  for (int i = 2; i <= n; i++)
  {
    int x;
    cin >> x;

    adj[x].push_back(i);
  }

  vector<int> dist(n + 1, -1);

  for (int i = 1; i <= n; i++)
  {
    if (dist[i] == -1)
    {

      solve(i, adj, dist);
    }
  }

  for (int i = 1; i <= n; i++)
  {
    cout << dist[i] << " ";
  }
}