#include "../World.h"
#include "Random.h"
#include "RecursiveBacktrackerExample.h"
#include <climits>
bool RecursiveBacktrackerExample::Step(World* w)
{
  if (!initialized && stack.empty()) {
    Point2D start = randomStartPoint(w);
    stack.push_back(start);
    w->SetNodeColor(start, Color::Crimson);
    initialized = true;
    return true;
  }
  if (initialized && stack.empty()) {
    return false;
  }

  auto currPoint = stack.back();

  auto visitables = getVisitables(w, currPoint);

  if (visitables.size() == 0) {
    w->SetNodeColor(currPoint, Color::Black);
    stack.pop_back();
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

void RecursiveBacktrackerExample::Clear(World* world) {
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
Point2D RecursiveBacktrackerExample::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  // todo: change this if you want
  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

std::vector<Point2D> RecursiveBacktrackerExample::getVisitables(World* w, const Point2D& p) {
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
