#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {
  auto side = world->getWorldSideSize() / 2;
  for (;;) {
    auto cat = world->getCat();
    Point2D p = {Random::Range(cat.x - 1, cat.x + 1), Random::Range(cat.y - 1, cat.y + 1)};
    if (cat.x != p.x && cat.y != p.y && !world->getContent(p)) return p;
  }
}
