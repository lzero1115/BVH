#include "box_box_intersect.h"

bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  for (int i = 0; i < 3; i++) {
    // If there is a gap along any axis, the boxes do not intersect
    if (A.min_corner(i) > B.max_corner(i) || B.min_corner(i) > A.max_corner(i)) {
      return false;
    }
  }
  // Overlapping on all three axes
  return true;
}