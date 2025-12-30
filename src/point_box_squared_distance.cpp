#include "point_box_squared_distance.h"
#include <algorithm>

double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double sqr_dist = 0.0;

  for (int i = 0; i < 3; ++i) {
    // Calculate the distance to the box along the i-th axis
    double dist_i = 0.0;
    if (query(i) < box.min_corner(i)) {
      dist_i = box.min_corner(i) - query(i);
    } else if (query(i) > box.max_corner(i)) {
      dist_i = query(i) - box.max_corner(i);
    }
    
    // Add the square of the 1D distance
    sqr_dist += dist_i * dist_i;
  }

  return sqr_dist;
  ////////////////////////////////////////////////////////////////////////////
}
