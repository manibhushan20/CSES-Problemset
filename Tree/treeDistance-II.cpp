#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;
vector<ll> subtree, dist;

ll solve(unordered_map<ll, vector<ll>> &adj, ll node, ll parent, ll d)
{
    dist[node] = d;
    ll cnt = 1; // count current node itself

    for (ll adjNode : adj[node])
    {
        if (adjNode == parent) continue;
        cnt += solve(adj, adjNode, node, d + 1);
    }

    subtree[node] = cnt;
    return cnt;
}

void reRoot(unordered_map<ll, vector<ll>> &adj, ll node, ll parent, vector<ll> &res)
{
    for (ll adjNode : adj[node])
    {
        if (adjNode == parent) continue;

        // subtree[adjNode] is full subtree size
        res[adjNode] = res[node] - subtree[adjNode] + (n - subtree[adjNode]);
        reRoot(adj, adjNode, node, res);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;

    subtree.assign(n + 1, 0);
    dist.assign(n + 1, 0);

    if (n == 1)
    {
        cout << 0 << '\n';
        return 0;
    }

    unordered_map<ll, vector<ll>> adj;

    for (int i = 0; i < n - 1; i++)
    {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    solve(adj, 1, 0, 0);

    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += dist[i];

    vector<ll> res(n + 1, 0);
    res[1] = sum;

    reRoot(adj, 1, 0, res);

    for (int i = 1; i <= n; i++)
    {
        cout << res[i] << " ";
    }

    return 0;
}