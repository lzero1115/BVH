#include "ray_intersect_box.h"
#include <iostream>

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
  ////////////////////////////////////////////////////////////////////////////
  double t_start = min_t;
  double t_end = max_t;

  for(int i = 0; i < 3; i++)
  {
    // Precompute inverse direction to handle potential division by zero correctly via infinity
    double invD = 1.0 / ray.direction(i);
    double t0 = (box.min_corner(i) - ray.origin(i)) * invD;
    double t1 = (box.max_corner(i) - ray.origin(i)) * invD;

    // If direction is negative, t0 will be greater than t1, so we swap them
    if (invD < 0.0) std::swap(t0, t1);

    // Update the global entry and exit points
    t_start = std::max(t_start, t0);
    t_end = std::min(t_end, t1);

    // If the interval becomes invalid, the ray misses the box
    if (t_start > t_end) return false;
  }

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
