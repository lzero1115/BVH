#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
  
  hit_t = max_t;
  hit_f = -1;
  bool hit = false;

  for (int f = 0; f < F.rows(); ++f) {
    double t;
    // Get the three vertices of the current triangle
    // F(f,0), F(f,1), F(f,2) are indices into the rows of V
    if (ray_intersect_triangle(
          ray, V.row(F(f,0)), V.row(F(f,1)), V.row(F(f,2)), 
          min_t, hit_t, t)) 
    {
      hit_t = t;
      hit_f = f;
      hit = true;
    }
  }

  return hit;
  ////////////////////////////////////////////////////////////////////////////
}
