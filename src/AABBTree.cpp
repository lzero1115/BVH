#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <algorithm>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  if (objects.empty()) {
    left = nullptr;
    right = nullptr;
    return;
  }

  // Handle the single object case (base case)
  if (objects.size() == 1) {
    left = objects[0];
    right = nullptr;
    this->box = objects[0]->box;
    return;
  }

  // Compute bounding box for all objects in this node
  this->box = BoundingBox();
  for (const auto& obj : objects) {
    insert_box_into_box(obj->box, this->box);
  }

  // Find the longest axis to split along
  Eigen::RowVector3d extent = this->box.max_corner - this->box.min_corner;
  int axis;
  extent.maxCoeff(&axis);
  double midpoint = 0.5 * (this->box.max_corner(axis) + this->box.min_corner(axis));

  // Partition objects based on their centers
  std::vector<std::shared_ptr<Object>> left_objects;
  std::vector<std::shared_ptr<Object>> right_objects;

  for (const auto& obj : objects) {
    if (obj->box.center()(axis) < midpoint) {
      left_objects.push_back(obj);
    } else {
      right_objects.push_back(obj);
    }
  }

  // Guard against infinite recursion if all object centers are identical
  if (left_objects.empty() || right_objects.empty()) {
    left_objects.clear();
    right_objects.clear();
    int half = objects.size() / 2;
    left_objects.assign(objects.begin(), objects.begin() + half);
    right_objects.assign(objects.begin() + half, objects.end());
  }

  // Recursively build the tree, but short-circuit if only 1 object remains
  // This avoids creating redundant AABBTree "wrappers"
  if (left_objects.size() == 1) {
    left = left_objects[0];
  } else {
    left = std::make_shared<AABBTree>(left_objects, depth + 1);
  }

  if (right_objects.size() == 1) {
    right = right_objects[0];
  } else {
    right = std::make_shared<AABBTree>(right_objects, depth + 1);
  }
}