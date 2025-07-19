#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n, m;
    cin >> n >> m;

    vector<vector<ll>> edges;
    for (int i = 0; i < m; i++) {
        ll u, v, c;
        cin >> u >> v >> c;
        edges.push_back({u, v, c});
    }

    vector<ll> dist(n + 1, LLONG_MIN);
    dist[1] = 0;
    

    // Relax all edges up to n-1 times
    for (int i = 1; i <= n - 1; i++) {
        for (auto &edge : edges) {
            ll u = edge[0], v = edge[1], c = edge[2];
            if (dist[u] != LLONG_MIN && dist[v] < dist[u] + c) {
                dist[v] = dist[u] + c;
            }
        }
    }

    // Check for positive cycles that can affect the path to node n
    vector<bool> in_cycle(n + 1, false);
    for (int i = 1; i <= n; i++) {
        for (auto &edge : edges) {
            ll u = edge[0], v = edge[1], c = edge[2];
            if (dist[u] != LLONG_MIN && dist[v] < dist[u] + c) {
                in_cycle[v] = true;
            }
        }
    }

    // Check if node n is reachable from any node in a positive cycle
    bool has_pos_cycle = false;
    vector<bool> visited(n + 1, false);
    queue<ll> q;
    for (int i = 1; i <= n; i++) {
        if (in_cycle[i]) {
            q.push(i);
            visited[i] = true;
        }
    }

    while (!q.empty()) {
        ll u = q.front();
        q.pop();
        for (auto &edge : edges) {
            if (edge[0] == u) {
                ll v = edge[1];
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
    }

    if (visited[n]) {
        cout << "-1" << endl;
    } else if (dist[n] == LLONG_MIN) {
        cout << "-1" << endl;
    } else {
        cout << dist[n] << endl;
    }

    return 0;
}