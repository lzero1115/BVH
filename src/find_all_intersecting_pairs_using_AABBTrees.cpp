#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
#include <list>

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > & 
    leaf_pairs)
{
  // 1. Initial check: If the root boxes don't even touch, no need to do anything
  if (!rootA || !rootB || !box_box_intersect(rootA->box, rootB->box)) {
    return;
  }

  // Use a simple queue for breadth-first-style traversal of tree pairs
  typedef std::pair<std::shared_ptr<Object>, std::shared_ptr<Object>> ObjectPair;
  std::list<ObjectPair> q;
  q.push_back({rootA, rootB});

  while (!q.empty()) {
    ObjectPair current = q.front();
    q.pop_front();

    std::shared_ptr<Object> objA = current.first;
    std::shared_ptr<Object> objB = current.second;

    // Check if boxes intersect (mandatory at each step)
    if (!box_box_intersect(objA->box, objB->box)) {
      continue;
    }

    // Try to cast both to AABBTree to see if they are internal nodes
    std::shared_ptr<AABBTree> nodeA = std::dynamic_pointer_cast<AABBTree>(objA);
    std::shared_ptr<AABBTree> nodeB = std::dynamic_pointer_cast<AABBTree>(objB);

    if (!nodeA && !nodeB) {
      // Case 1: Both are leaves
      leaf_pairs.push_back({objA, objB});
    } else if (!nodeA) {
      // Case 2: A is a leaf, B is an internal node
      if (nodeB->left)  q.push_back({objA, nodeB->left});
      if (nodeB->right) q.push_back({objA, nodeB->right});
    } else if (!nodeB) {
      // Case 3: B is a leaf, A is an internal node
      if (nodeA->left)  q.push_back({nodeA->left, objB});
      if (nodeA->right) q.push_back({nodeA->right, objB});
    } else {
      // Case 4: Both are internal nodes
      if (nodeA->left && nodeB->left)   q.push_back({nodeA->left,  nodeB->left});
      if (nodeA->left && nodeB->right)  q.push_back({nodeA->left,  nodeB->right});
      if (nodeA->right && nodeB->left)  q.push_back({nodeA->right, nodeB->left});
      if (nodeA->right && nodeB->right) q.push_back({nodeA->right, nodeB->right});
    }
  }
}