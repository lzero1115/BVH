#include "point_AABBTree_squared_distance.h"
#include "point_box_squared_distance.h"
#include <queue>
#include <limits>

bool point_AABBTree_squared_distance(
  const Eigen::RowVector3d & query,
  const std::shared_ptr<AABBTree> & root,
  const double min_sqrd,
  const double max_sqrd,
  double & sqrd,
  std::shared_ptr<Object> & descendant)
{
  typedef std::pair<double, std::shared_ptr<Object>> HeapItem;

  std::priority_queue<HeapItem, std::vector<HeapItem>, std::greater<HeapItem>> pq; 
  //smallest distance has highest priority, on top

  sqrd = std::numeric_limits<double>::infinity();
  
  double d_root = point_box_squared_distance(query, root->box);
  pq.push({d_root, root});

  bool found = false;

  while (!pq.empty()) {
    HeapItem top = pq.top();
    pq.pop();

    double d_box = top.first;
    std::shared_ptr<Object> obj = top.second;

    if (d_box >= sqrd) {
      break;
    }

    std::shared_ptr<AABBTree> node = std::dynamic_pointer_cast<AABBTree>(obj);

    if (node) {
      if (node->left) {
        pq.push({point_box_squared_distance(query, node->left->box), node->left});
      }
      if (node->right) {
        pq.push({point_box_squared_distance(query, node->right->box), node->right});
      }
    } else {
      double d_actual;
      std::shared_ptr<Object> d_obj;
      if (obj->point_squared_distance(query, min_sqrd, max_sqrd, d_actual, d_obj)) {
        if (d_actual < sqrd) {
          sqrd = d_actual;
          descendant = obj;
          found = true;
        }
      }
    }
  }

  return (sqrd >= min_sqrd && sqrd <= max_sqrd && found);
}