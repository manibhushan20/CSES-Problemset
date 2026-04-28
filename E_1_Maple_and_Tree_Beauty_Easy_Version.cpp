#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<ll> len;

void dfs(unordered_map<ll, vector<ll>> &adj, ll u, vector<ll> &temp, vector<vector<ll>> &paths)
{
  temp.push_back(u);
  if (adj[u].empty())
  {
    len.push_back(temp.size());
    paths.push_back(temp);
  }
  else
  {
    for (auto v : adj[u])
    {
      dfs(adj, v, temp, paths);
    }
  }
  temp.pop_back();
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll t;
  cin >> t;

  while (t--)
  {
    len.clear();

    ll n, k;
    cin >> n >> k;

    vector<ll> p(n + 1);
    for (ll i = 1; i < n; i++)
      cin >> p[i];

    unordered_map<ll, vector<ll>> adj;
    for (ll i = 1; i < n; i++)
    {
      adj[p[i]].push_back(i + 1); // parent → child
    }

    vector<ll> temp;
    vector<vector<ll>> paths;
    dfs(adj, 1, temp, paths);

    ll sz = len.size();
    if (sz == 0)
    {
      cout << 0 << "\n";
      continue;
    }

   
    int res = 0;
   
  

    cout << res << endl;
  }
}
