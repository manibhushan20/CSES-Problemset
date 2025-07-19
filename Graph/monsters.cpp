#include <bits/stdc++.h>
using namespace std;

static const vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
static const string dirChars = "DURL";

void bfs_dist(queue<pair<int, int>> &q, vector<vector<int>> &dist, const vector<string> &grid, int n, int m) {
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;
        for (int i = 0; i < 4; ++i) {
            int nx = x + directions[i].first;
            int ny = y + directions[i].second;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                q.emplace(nx, ny);
            }
        }
    }
}

vector<vector<char>> bfs_with_parent(queue<pair<int, int>> &q, vector<vector<int>> &dist, 
                                    const vector<string> &grid, int n, int m) {
    vector<vector<char>> parent(n, vector<char>(m, '#'));
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int x = cur.first, y = cur.second;
        for (int i = 0; i < 4; ++i) {
            int nx = x + directions[i].first;
            int ny = y + directions[i].second;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m &&
                grid[nx][ny] != '#' && dist[nx][ny] == -1) {
                dist[nx][ny] = dist[x][y] + 1;
                parent[nx][ny] = dirChars[i];
                q.emplace(nx, ny);
            }
        }
    }
    return parent;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<string> grid(n);
    for (int i = 0; i < n; ++i) cin >> grid[i];

    vector<vector<int>> distMon(n, vector<int>(m, -1));
    vector<vector<int>> distPer(n, vector<int>(m, -1));
    queue<pair<int, int>> qMon, qPer;

    // Initialize queues
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'M') {
                distMon[i][j] = 0;
                qMon.emplace(i, j);
            } else if (grid[i][j] == 'A') {
                distPer[i][j] = 0;
                qPer.emplace(i, j);
            }
        }
    }

    // Compute monster distances
    bfs_dist(qMon, distMon, grid, n, m);

    // Compute person distances and parents
    auto parent = bfs_with_parent(qPer, distPer, grid, n, m);

    // Find exit on border
    int ex = -1, ey = -1;
    for (int i = 0; i < n && ex == -1; ++i) {
        for (int j = 0; j < m; ++j) {
            if ((i == 0 || j == 0 || i == n-1 || j == m-1) && 
                distPer[i][j] != -1 && 
                (distMon[i][j] == -1 || distPer[i][j] < distMon[i][j])) {
                ex = i;
                ey = j;
                break;
            }
        }
    }

    if (ex == -1) {
        cout << "NO\n";
        return 0;
    }

    // Reconstruct path
    string path;
    int x = ex, y = ey;
    while (parent[x][y] != '#') {
        char c = parent[x][y];
        path.push_back(c);
        // Reverse the move to trace back to start
        switch (c) {
            case 'D': x--; break;
            case 'U': x++; break;
            case 'R': y--; break;
            case 'L': y++; break;
        }
    }
    reverse(path.begin(), path.end());

    cout << "YES\n" << path.size() << "\n" << path << "\n";
    return 0;
}