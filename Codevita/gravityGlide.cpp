#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Slope
{
  int x1, y1, x2, y2;
  int slopeKind; // 0: vertical, 1: slope 1, -1: slope -1
  int c;
  int minX, maxX;
};

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int slopeCount;
  cin >> slopeCount;

  vector<Slope> slopes(slopeCount);
  for (int i = 0; i < slopeCount; ++i)
  {
    cin >> slopes[i].x1 >> slopes[i].y1 >> slopes[i].x2 >> slopes[i].y2;
    slopes[i].minX = min(slopes[i].x1, slopes[i].x2);
    slopes[i].maxX = max(slopes[i].x1, slopes[i].x2);

    if (slopes[i].x1 == slopes[i].x2)
    {
      slopes[i].slopeKind = 0;
      slopes[i].c = 0;
    }
    else
    {
      int slopeVal = (slopes[i].y2 - slopes[i].y1) / (slopes[i].x2 - slopes[i].x1);
      if (slopeVal == 1)
      {
        slopes[i].slopeKind = 1;
        slopes[i].c = slopes[i].y1 - slopes[i].x1;
      }
      else
      {
        slopes[i].slopeKind = -1;
        slopes[i].c = slopes[i].y1 + slopes[i].x1;
      }
    }
  }

  int posX, posY;
  long long power;
  cin >> posX >> posY >> power;

  while (posY > 0)
  {
    bool hasMoved = false;
    vector<int> activeSlopes;
    int slideIdx = -1;
    int moveDir = 0;

    for (int i = 0; i < slopeCount; ++i)
    {
      if (posX < slopes[i].minX || posX > slopes[i].maxX)
        continue;

      bool isOnSlope = false;
      if (slopes[i].slopeKind == 1 && posY - posX == slopes[i].c)
        isOnSlope = true;
      if (slopes[i].slopeKind == -1 && posY + posX == slopes[i].c)
        isOnSlope = true;

      if (isOnSlope)
      {
        activeSlopes.push_back(i);
        if (slopes[i].slopeKind == 1 && posX > slopes[i].minX)
        {
          slideIdx = i;
          moveDir = -1;
        }
        if (slopes[i].slopeKind == -1 && posX < slopes[i].maxX)
        {
          slideIdx = i;
          moveDir = 1;
        }
      }
    }

    if (activeSlopes.size() > 1)
    {
      long long unlockCost = (long long)posX * posY;
      if (power >= unlockCost)
      {
        power -= unlockCost;
        if (slideIdx != -1 && power > 0)
        {
          posX += moveDir;
          posY--;
          power--;
          hasMoved = true;
        }
        else if (slideIdx != -1 && power == 0)
        {
          break;
        }
      }
      else
      {
        break;
      }
    }
    else if (slideIdx != -1)
    {
      if (power > 0)
      {
        posX += moveDir;
        posY--;
        power--;
        hasMoved = true;
      }
      else
      {
        break;
      }
    }

    if (!hasMoved)
    {
      int nextY = 0;
      for (int i = 0; i < slopeCount; ++i)
      {
        if (posX >= slopes[i].minX && posX <= slopes[i].maxX)
        {
          int yIntersect = -1;
          if (slopes[i].slopeKind == 1)
            yIntersect = posX + slopes[i].c;
          else if (slopes[i].slopeKind == -1)
            yIntersect = slopes[i].c - posX;

          if (yIntersect != -1 && yIntersect < posY && yIntersect > nextY)
          {
            nextY = yIntersect;
          }
        }
      }
      if (posY == nextY)
      {
        break;
      }
      posY = nextY;
      if (posY == 0)
      {
        break;
      }
    }
  }

  cout << posX << " " << posY;
  return 0;
}
