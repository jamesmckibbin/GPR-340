#include "HuntAndKillExample.h"
#include "../World.h"
#include "Random.h"
#include <climits>
bool HuntAndKillExample::Step(World* w)
{
  if (!initialized) {
    Point2D zero = randomStartPoint(w);
    stack.push_back(zero);
    w->SetNodeColor(zero, Color::Crimson);
    initialized = true;
    return true;
  }
  if (initialized && stack.empty()) {
    return false;
  }

  auto currPoint = stack.back();

  auto visitables = getVisitables(w, currPoint);

  if (visitables.size() == 0) 
  {
    for (auto point : stack)
    {
      w->SetNodeColor(point, Color::Black);
      visited[point.y][point.x] = true;
    }

    stack.clear();

    Point2D newStart = randomStartPoint(w);
    if (newStart.x == INT_MAX) 
    {
      return false;
    }
    w->SetNodeColor(newStart, Color::Crimson);
    auto neighbors = getVisitedNeighbors(w, newStart);
    auto parent = neighbors[Random::Range(0, neighbors.size() - 1)];

    if (parent == newStart.Left()) { 
      w->SetWest(newStart, false);
    } else if (parent == newStart.Down()) {
      w->SetSouth(newStart, false);
    } else if (parent == newStart.Right()) {
      w->SetEast(newStart, false);
    } else if (parent == newStart.Up()) {
      w->SetNorth(newStart, false);
    }

    stack.push_back(newStart);

    return true;
  }

  auto nextPoint = visitables[Random::Range(0, visitables.size() - 1)];
  stack.push_back(nextPoint);
  w->SetNodeColor(nextPoint, Color::Crimson);

  if (nextPoint == currPoint.Left()) {
    w->SetWest(currPoint, false);
  } else if (nextPoint == currPoint.Down()) {
    w->SetSouth(currPoint, false);
  } else if (nextPoint == currPoint.Right()) {
    w->SetEast(currPoint, false);
  } else if (nextPoint == currPoint.Up()) {
    w->SetNorth(currPoint, false);
  }

  return true;
}
void HuntAndKillExample::Clear(World* world) {
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }

  initialized = false;
}

Point2D HuntAndKillExample::randomStartPoint(World* world) {
  // Todo: improve this if you want
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> HuntAndKillExample::getVisitables(World* w, const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;
  auto clearColor = Color::DarkGray;

  if (p.x > -sideOver2 && w->GetNodeColor(p.Left()) == clearColor) {
    visitables.push_back(p.Left());
  }
  if (p.y < sideOver2 && w->GetNodeColor(p.Down()) == clearColor) {
    visitables.push_back(p.Down());
  }
  if (p.x < sideOver2 && w->GetNodeColor(p.Right()) == clearColor) {
    visitables.push_back(p.Right());
  }
  if (p.y > -sideOver2 && w->GetNodeColor(p.Up()) == clearColor) {
    visitables.push_back(p.Up());
  }
  return visitables;
}
std::vector<Point2D> HuntAndKillExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> neighbors;

  if (p.x > -sideOver2 && w->GetNodeColor(p.Left()) == Color::Black) {
    neighbors.push_back(p.Left());
  }
  if (p.y < sideOver2 && w->GetNodeColor(p.Down()) == Color::Black) {
    neighbors.push_back(p.Down());
  }
  if (p.x < sideOver2 && w->GetNodeColor(p.Right()) == Color::Black) {
    neighbors.push_back(p.Right());
  }
  if (p.y > -sideOver2 && w->GetNodeColor(p.Up()) == Color::Black) {
    neighbors.push_back(p.Up());
  }

  return neighbors;
}
