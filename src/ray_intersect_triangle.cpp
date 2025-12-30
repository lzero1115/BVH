#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d a = A.transpose();
  Eigen::Vector3d b = B.transpose();
  Eigen::Vector3d c = C.transpose();

  Eigen::Vector3d edge1 = b - a;
  Eigen::Vector3d edge2 = c - a;

  Eigen::Vector3d pvec = ray.direction.cross(edge2);
  double det = edge1.dot(pvec);

  if (std::abs(det) < 1e-10) {
    return false;
  }

  double inv_det = 1.0 / det;
  Eigen::Vector3d tvec = ray.origin - a;

  double u = tvec.dot(pvec) * inv_det;
  if (u < 0.0 || u > 1.0) {
    return false;
  }

  Eigen::Vector3d qvec = tvec.cross(edge1);
  double v = ray.direction.dot(qvec) * inv_det;
  if (v < 0.0 || u + v > 1.0) {
    return false;
  }

  double temp_t = edge2.dot(qvec) * inv_det;

  if (temp_t >= min_t && temp_t <= max_t) {
    t = temp_t;
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}

