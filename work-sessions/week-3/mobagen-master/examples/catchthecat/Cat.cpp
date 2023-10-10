#include "Cat.h"

#include <map>

#include "World.h"

Point2D Cat::Move(World* world)
{
  auto pos = world->getCat();
  std::map<Point2D, int> costList;

  for (int y = -world->getWorldSideSize(); y <= world->getWorldSideSize(); y++) 
  {
    for (int x = -world->getWorldSideSize(); x <= world->getWorldSideSize(); x++) 
    {
      Point2D point = Point2D(x, y);
      costList[point] = Random::Range(0, 10);
    }
  }

  Point2D pointToMoveTo = pos;
  int costToMoveTo = 0;

  for (auto neighbor : world->neighbors(pos)) 
  {
    if (world->catCanMoveToPosition(neighbor)) 
    {
      if (costToMoveTo == 0) 
      {
        costToMoveTo = costList[neighbor];
        pointToMoveTo = neighbor;
      }
      else if (costToMoveTo >= costList[neighbor]) 
      {
        costToMoveTo = costList[neighbor];
        pointToMoveTo = neighbor;
      }
    }
  }

  return pointToMoveTo;
}


