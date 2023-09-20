#include "PrimExample.h"
#include "../World.h"
#include "Random.h"

bool PrimExample::Step(World* w) {
  int sideOver2 = w->GetSize() / 2;

  // read through toBeVisited and pick a random node
  // set node to 1 and change color

  if (!initialized) 
  {
    Point2D zero = Point2D(0, 0);
    toBeVisited.push_back(zero);
    w->SetNodeColor(zero, Color::DarkSalmon);
    initialized = true;
    return true;
  }

  if (!toBeVisited.empty()) {

    int randNum = Random::Range(0, toBeVisited.size() - 1);

    Point2D nextPoint = toBeVisited[randNum];
    w->SetNodeColor(nextPoint, Color::Black);
    toBeVisited.erase(std::ranges::remove(toBeVisited, nextPoint).begin(), toBeVisited.end());

    for (auto point : getVisitables(w, nextPoint)) {
      toBeVisited.push_back(point);
      w->SetNodeColor(point, Color::DarkSalmon);
    }

    auto visited = getVisitedNeighbors(w, nextPoint);
    if (visited.size() == 0) {
      return false;
    }

    Point2D parent = visited[Random::Range(0, visited.size() - 1)];

    if (nextPoint == parent.Left()) {
      w->SetWest(parent, false);
    } else if (nextPoint == parent.Down()) {
      w->SetSouth(parent, false);
    } else if (nextPoint == parent.Right()) {
      w->SetEast(parent, false);
    } else if (nextPoint == parent.Up()) {
      w->SetNorth(parent, false);
    }
  }

  return true;
}
void PrimExample::Clear(World* world) {
  toBeVisited.clear();
  initialized = false;
}

std::vector<Point2D> PrimExample::getVisitables(World* w, const Point2D& p) {
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

std::vector<Point2D> PrimExample::getVisitedNeighbors(World* w, const Point2D& p) {
  std::vector<Point2D> deltas = {Point2D::UP, Point2D::DOWN, Point2D::LEFT, Point2D::RIGHT};
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
