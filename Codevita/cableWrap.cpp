#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<string> grid(rows);
  for (int i = 0; i < rows; i++)
  {
    grid[i].resize(cols);
    for (int j = 0; j < cols; j++)
      cin >> grid[i][j];
  }

  vector<int> fullRows, fullCols;
  for (int i = 0; i < rows; i++)
  {
    if (all_of(grid[i].begin(), grid[i].end(), [](char c)
               { return c != '.'; }))
      fullRows.push_back(i);
  }

  for (int j = 0; j < cols; j++)
  {
    bool full = true;
    for (int i = 0; i < rows; i++)
      if (grid[i][j] == '.')
        full = false;
    if (full)
      fullCols.push_back(j);
  }

  vector<vector<bool>> hasCross(rows, vector<bool>(cols, false));

  for (int col : fullCols)
  {
    for (int i = 0; i < rows; i++)
    {
      int left = col - 1, right = col + 1;
      if (left >= 0 && right < cols && grid[i][left] == 'C' && grid[i][right] == 'C')
        hasCross[i][col] = true;
    }
  }

  for (int row : fullRows)
  {
    for (int j = 0; j < cols; j++)
    {
      int up = row - 1, down = row + 1;
      if (up >= 0 && down < rows && grid[up][j] == 'C' && grid[down][j] == 'C')
        hasCross[row][j] = true;
    }
  }

  vector<vector<bool>> hasCable(rows, vector<bool>(cols, false));
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++)
      if (grid[i][j] == 'C' || hasCross[i][j])
        hasCable[i][j] = true;

  vector<vector<int>> graph(rows * cols);
  int dr[4] = {-1, 0, 1, 0};
  int dc[4] = {0, 1, 0, -1};

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (!hasCable[i][j])
        continue;
      int id = i * cols + j;
      for (int d = 0; d < 4; d++)
      {
        int ni = i + dr[d], nj = j + dc[d];
        if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && hasCable[ni][nj])
          graph[id].push_back(ni * cols + nj);
      }
    }
  }

  int startNode = -1;
  for (int i = 0; i < rows && startNode == -1; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (hasCable[i][j] && graph[i * cols + j].size() == 1)
      {
        startNode = i * cols + j;
        break;
      }
    }
  }

  vector<bool> visited(rows * cols, false);
  vector<int> rowSum(rows, 0), colSum(cols, 0);

  int current = startNode, previous = -1;
  visited[current] = true;

  while (true)
  {
    int r = current / cols, c = current % cols;
    int nextNode = -1;
    for (int neighbor : graph[current])
    {
      if (neighbor != previous && !visited[neighbor])
      {
        nextNode = neighbor;
        break;
      }
    }

    if (hasCross[r][c] && previous != -1)
    {
      int prevRow = previous / cols, prevCol = previous % cols;
      int sign = (grid[r][c] == 'C') ? 1 : -1;

      if (prevRow == r)
        colSum[c] += ((prevCol < c) ? 1 : -1) * sign;
      else
        rowSum[r] += ((prevRow < r) ? 1 : -1) * sign;
    }

    if (nextNode == -1)
      break;
    previous = current;
    current = nextNode;
    visited[current] = true;
  }

  long long total = 0;
  for (int r : fullRows)
    total += abs(rowSum[r]) / 2;
  for (int c : fullCols)
    total += abs(colSum[c]) / 2;

  cout << total;
  return 0;
}
