#ifndef CAT_H
#define CAT_H

#include "Agent.h"
#include "Random.h"

class Cat : public Agent {
public:
  explicit Cat() : Agent(){};
  Point2D Move(World*) override;
  int directionToMove = Random::Range(0, 5);
};

#endif  // CAT_H
