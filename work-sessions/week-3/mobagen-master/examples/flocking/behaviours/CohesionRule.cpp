#include "CohesionRule.h"
#include "../gameobjects/Boid.h"

Vector2f CohesionRule::computeForce(const std::vector<Boid*>& neighborhood, Boid* boid) {
  Vector2f cohesionForce = Vector2f::zero();
  Vector2f avgPosition = Vector2f::zero();

  // todo: add your code here to make a force towards the center of mass
  // hint: iterate over the neighborhood
  if (neighborhood.size() != 0) {
    for (auto* neighbor : neighborhood) {
      avgPosition += neighbor->getPosition();
    }
    avgPosition /= neighborhood.size();

    cohesionForce = (avgPosition - boid->getPosition()).normalized();
  }

  return cohesionForce.normalized();
}