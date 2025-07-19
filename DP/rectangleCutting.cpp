
#include <bits/stdc++.h>
#define ll long long

using namespace std;

int main()
{

  int a, b;
  cin >> a >> b;

  int dp[a + 1][b + 1];

  for (int height = 1; height <= a; height++)
  {
    for (int width = 1; width <= b; width++)
    {
      if (height == width)
        dp[height][width] = 0;
      else
      {
        int ans = 1e8;
        for (int i = 1; i < width; i++)
          ans = min(ans, 1 + dp[height][width - i] + dp[height][i]);

        for (int i = 1; i < height; i++)
          ans = min(ans, 1 + dp[height - i][width] + dp[i][width]);
          
        dp[height][width] = ans;
      }
    }
  }

  cout << dp[a][b];

  return 0;
}