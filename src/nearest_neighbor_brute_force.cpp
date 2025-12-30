#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  sqrD = std::numeric_limits<double>::infinity();
  I = -1;

  for (int i = 0; i < points.rows(); i++) {
    // Calculate squared Euclidean distance
    double d2 = (points.row(i) - query).squaredNorm();
    
    if (d2 < sqrD) {
      sqrD = d2;
      I = i;
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}
