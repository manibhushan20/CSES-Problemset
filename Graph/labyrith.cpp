#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
string pathMap = "DURL";

int main()
{
  int n, m;
  cin >> n >> m;
  vector<vector<char>> grid(n, vector<char>(m));
  pair<int, int> start, end;

  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      cin >> grid[i][j];
      if (grid[i][j] == 'A')
        start = {i, j};
      if (grid[i][j] == 'B')
        end = {i, j};
    }
  }

  vector<vector<int>> prevDir(n, vector<int>(m, -1));
  queue<pair<int, int>> q;
  q.push(start);
  vector<vector<int>> vis(n, vector<int>(m, 0));
  vis[start.first][start.second] = 1;

  bool found = false;
  while (!q.empty())
  {
    auto it = q.front();
    int x = it.first;
    int y = it.second;
    q.pop();
    if (x == end.first && y == end.second)
    {
      found = true;
      break;
    }
    for (int k = 0; k < 4; k++)
    {
      int nx = x + dirs[k].first;
      int ny = y + dirs[k].second;
      if (nx >= 0 && ny >= 0 && nx < n && ny < m && !vis[nx][ny] && grid[nx][ny] != '#')
      {
        vis[nx][ny] = 1;
        prevDir[nx][ny] = k;
        q.push({nx, ny});
      }
    }
  }

  if (!found)
  {
    cout << "NO\n";
    return 0;
  }

  // reconstruct path
  string path;
  int x = end.first, y = end.second;
  while (make_pair(x, y) != start)
  {
    int k = prevDir[x][y];
    path.push_back(pathMap[k]);
    x -= dirs[k].first;
    y -= dirs[k].second;
  }
  reverse(path.begin(), path.end());

  cout << "YES\n"
       << path.size() << "\n"
       << path << "\n";
}
