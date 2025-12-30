#include "triangle_triangle_intersection.h"
#include <Eigen/Geometry>
#include <vector>
#include <algorithm>

// Helper function to project triangle onto an axis and check for overlap
bool is_separating_axis(
  const Eigen::RowVector3d & axis,
  const Eigen::RowVector3d & A0, const Eigen::RowVector3d & A1, const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0, const Eigen::RowVector3d & B1, const Eigen::RowVector3d & B2)
{
  if (axis.squaredNorm() < 1e-10) return false; // Ignore degenerate axes

  auto project = [&](const Eigen::RowVector3d & p) { return p.dot(axis); };

  double minA = std::min({project(A0), project(A1), project(A2)});
  double maxA = std::max({project(A0), project(A1), project(A2)});
  double minB = std::min({project(B0), project(B1), project(B2)});
  double maxB = std::max({project(B0), project(B1), project(B2)});

  // If there's a gap, this is a separating axis
  return (maxA < minB || maxB < minA);
}

bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0, const Eigen::RowVector3d & A1, const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0, const Eigen::RowVector3d & B1, const Eigen::RowVector3d & B2)
{
  // 1. Get edges for both triangles
  Eigen::RowVector3d edgeA[] = {A1 - A0, A2 - A1, A0 - A2};
  Eigen::RowVector3d edgeB[] = {B1 - B0, B2 - B1, B0 - B2};

  // 2. Get normals for both triangles
  Eigen::RowVector3d normalA = edgeA[0].cross(edgeA[1]);
  Eigen::RowVector3d normalB = edgeB[0].cross(edgeB[1]);

  // 3. Collect all 11 axes to test
  std::vector<Eigen::RowVector3d> axes;
  axes.push_back(normalA);
  axes.push_back(normalB);

  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      axes.push_back(edgeA[i].cross(edgeB[j]));
    }
  }

  // 4. Test each axis
  for (const auto& axis : axes) {
    if (is_separating_axis(axis, A0, A1, A2, B0, B1, B2)) {
      return false; // Found a gap!
    }
  }

  return true; // No gap found on any axis
}