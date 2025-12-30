#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (!ray_intersect_box(ray, this->box, min_t, max_t)) {
    return false;
  }

  double t_left, t_right;
  std::shared_ptr<Object> desc_left = nullptr, desc_right = nullptr;

  bool hit_left = (left != nullptr) && left->ray_intersect(ray, min_t, max_t, t_left, desc_left);
  double new_max_t = hit_left ? t_left : max_t;

  bool hit_right = (right != nullptr) && right->ray_intersect(ray, min_t, new_max_t, t_right, desc_right);

  if (hit_right) {
    // Due to the new_max_t constraint, if hit_right is true,
    // it's guaranteed to be closer than (or equal to) any hit in the left child.
    t = t_right;
    // If desc_right is nullptr, it means we hit a leaf, so use right directly
    descendant = desc_right ? desc_right : right;
    return true;
  } else if (hit_left) {
    t = t_left;
    // If desc_left is nullptr, it means we hit a leaf, so use left directly
    descendant = desc_left ? desc_left : left;
    return true;
  }

  return false;


  
  ////////////////////////////////////////////////////////////////////////////
}

