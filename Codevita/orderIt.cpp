#include <bits/stdc++.h>
using namespace std;

// Custom hash for vector<int>
struct VectorHash
{
  size_t operator()(const vector<int> &v) const
  {
    size_t hashValue = 0;
    for (int x : v)
      hashValue = hashValue * 31 + x;
    return hashValue;
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  string label;
  cin >> label;
  cin.ignore();

  vector<string> scrambledList(n), correctList(n);

  for (int i = 0; i < n; i++)
    getline(cin, scrambledList[i]);

  cin >> label;
  cin.ignore();

  for (int i = 0; i < n; i++)
    getline(cin, correctList[i]);

  unordered_map<string, int> indexMap;
  for (int i = 0; i < n; i++)
    indexMap[correctList[i]] = i;

  vector<int> startOrder(n), goalOrder(n);
  for (int i = 0; i < n; i++)
    startOrder[i] = indexMap[scrambledList[i]];

  iota(goalOrder.begin(), goalOrder.end(), 0);

  if (startOrder == goalOrder)
  {
    cout << 0;
    return 0;
  }

  unordered_map<vector<int>, int, VectorHash> distStart, distGoal;
  queue<vector<int>> qStart, qGoal;

  distStart[startOrder] = 0;
  distGoal[goalOrder] = 0;
  qStart.push(startOrder);
  qGoal.push(goalOrder);

  auto expand = [&](queue<vector<int>> &q,
                    unordered_map<vector<int>, int, VectorHash> &distA,
                    unordered_map<vector<int>, int, VectorHash> &distB) -> int
  {
    int levelSize = q.size();
    while (levelSize--)
    {
      auto current = q.front();
      q.pop();
      int steps = distA[current];

      for (int left = 0; left < n; left++)
      {
        for (int right = left; right < n; right++)
        {
          vector<int> segment(current.begin() + left, current.begin() + right + 1);
          vector<int> remaining;
          for (int i = 0; i < n; i++)
            if (i < left || i > right)
              remaining.push_back(current[i]);

          for (int pos = 0; pos <= (int)remaining.size(); pos++)
          {
            vector<int> nextState = remaining;
            nextState.insert(nextState.begin() + pos, segment.begin(), segment.end());

            if (distA.count(nextState))
              continue;

            distA[nextState] = steps + 1;
            if (distB.count(nextState))
              return steps + 1 + distB[nextState];

            q.push(nextState);
          }
        }
      }
    }
    return -1;
  };

  while (!qStart.empty() && !qGoal.empty())
  {
    int res = expand(qStart, distStart, distGoal);
    if (res != -1)
    {
      cout << res;
      return 0;
    }

    res = expand(qGoal, distGoal, distStart);
    if (res != -1)
    {
      cout << res;
      return 0;
    }
  }

  cout << -1;
  return 0;
}
