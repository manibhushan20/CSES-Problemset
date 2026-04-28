#include <bits/stdc++.h>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  if (!(cin >> rows >> cols))
    return 0;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  vector<int> starCount(cols, 0);
  for (int i = 0; i < rows; ++i)
  {
    string line, tmp;
    getline(cin, line);
    for (char ch : line)
      if (ch != ' ')
        tmp.push_back(ch);
    for (int j = 0; j < cols; ++j)
      if (tmp[j] == '*')
        ++starCount[j];
  }

  int moves;
  cin >> moves;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int t = 0; t < moves; ++t)
  {
    string dir;
    getline(cin, dir);

    vector<int> freq(rows + 1, 0);
    for (int v : starCount)
      ++freq[v];

    vector<int> suf(rows + 2, 0);
    int cur = 0;
    for (int x = rows; x >= 0; --x)
    {
      cur += freq[x];
      suf[x] = cur;
    }

    int newRows = cols, newCols = rows;
    vector<int> next(newCols, 0);

    if (dir == "right")
    {
      for (int i = 0; i < newCols; ++i)
        next[i] = suf[i + 1];
    }
    else
    {
      for (int i = 0; i < newCols; ++i)
        next[i] = suf[rows - i];
    }

    rows = newRows;
    cols = newCols;
    starCount.swap(next);
  }

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      char ch = (i >= rows - starCount[j]) ? '*' : '.';
      cout << ch;
    }
    cout << '\n';
  }

  return 0;
}
