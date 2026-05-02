#include <bits/stdc++.h>
using namespace std;


const int MAXN = 200005;
vector<int> adj[MAXN];
bool matched[MAXN];
int ans = 0;

void dfs(int u, int p)
{
  for (int v : adj[u])
  {
    if (v == p)
      continue; 

    // 1. Go all the way to the leaves first (Depth First)
    dfs(v, u);

    // 2. Post-order logic: On the way back up, check if we can match
    // If the child (v) is not matched AND the parent (u) is not matched
    if (!matched[v] && !matched[u])
    {
      matched[u] = true;
      matched[v] = true;
      ans++;
    }
  }
}

int main()
{
  
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  if (!(cin >> n))
    return 0;

  // Handle edge case for n=1
  if (n < 2)
  {
    cout << 0 << endl;
    return 0;
  }

  for (int i = 0; i < n - 1; i++)
  {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dfs(1, 0); // Start DFS from an arbitrary root (node 1)

  cout << ans << endl;

  return 0;
}