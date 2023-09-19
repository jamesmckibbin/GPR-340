//
// Created by atolstenko on 2/9/2023.
//

#include "HexagonGameOfLife.h"
void HexagonGameOfLife::Step(World& world)
{
  for (int i = 0; i < world.SideSize(); i++) 
  {
    for (int j = 0; j < world.SideSize(); j++) 
    {
      Point2D currPoint = Point2D(i, j);
      int numNeighbors = CountNeighbors(world, currPoint);

      if (numNeighbors < 2 && world.Get(currPoint) == true) 
      {
        world.SetNext(currPoint, false);
      }
      if (numNeighbors == 2) 
      {
        world.SetNext(currPoint, true);
      }
      if (numNeighbors >= 3 && world.Get(currPoint) == true) 
      {
        world.SetNext(currPoint, false);
      }
    }
  }

  world.SwapBuffers();
}
int HexagonGameOfLife::CountNeighbors(World& world, Point2D point)
{
  int count = 0;

  if (point.y % 2 == 1) // Odd
  {
    count += world.Get(point.Up()) ? 1 : 0;
    count += world.Get(point.Up().Right()) ? 1 : 0;
    count += world.Get(point.Left()) ? 1 : 0;
    count += world.Get(point.Right()) ? 1 : 0;
    count += world.Get(point.Down()) ? 1 : 0;
    count += world.Get(point.Down().Right()) ? 1 : 0;
  }
  else if (point.y % 2 == 0) // Even
  {
    count += world.Get(point.Up().Left()) ? 1 : 0;
    count += world.Get(point.Up()) ? 1 : 0;
    count += world.Get(point.Left()) ? 1 : 0;
    count += world.Get(point.Right()) ? 1 : 0;
    count += world.Get(point.Down().Left()) ? 1 : 0;
    count += world.Get(point.Down()) ? 1 : 0;
  }

  return count;
}
