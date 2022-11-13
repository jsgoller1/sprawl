#include "MathHelpers.hh"

bool rangeContainsVal(const real a, const real b, const real val) {
  if (eq(a, b)) {
    /*
     * If a and b are equal under a certain margin of error, treat val as equal
     * to them both if it's equal to either under the same margin of error.
     * Technically this is not correct, but the margin of error is so small that
     * it won't matter.
     */
    return eq(a, val) || eq(b, val);
  } else if (lt(a, b)) {
    return lte(a, val) && lte(val, b);
  } else {
    return gte(a, val) && gte(val, b);
  }
}

bool intervalsOverlap(const PositionUnit low1, const PositionUnit hi1,
                      const PositionUnit low2, const PositionUnit hi2) {
  /*
   * If A and B are closed intervals [A.l, A.r] and [B.l, B.r] respectively,
   they overlap segments on the name To do 2D collision testing, we need to do
   two separate 1D line intersection tests; if both intersect, a 2D collision
   occurs. For two straight lines A and B (each with start and end points l and
   r, though this works for vertical lines too), we have four cases to check:
    - The right side of A intersects with B:
      B.l <= A.r <= B.r
    - The left side of A intersects with B:
      B.l <= A.l <= B.r
    - A falls completely in B:
      B.l <= A.l < A.r <= B.r
    - B falls completely within A:
      A.l <= B.l < B.r <= A.r
  */
  bool low2Intersects = (lte(low1, low2) && lte(low2, hi1));
  bool hi2Intersects = (lte(low1, hi2) && lte(hi2, hi1));
  bool containedIn1 = (lte(low1, low2) && lte(hi2, hi1));
  bool containedIn2 = (lte(low2, low1) && lte(hi1, hi2));
  return low2Intersects || hi2Intersects || containedIn1 || containedIn2;
}

PointOrientation getOrientation(const Vect2D& p1, const Vect2D& p2,
                                const Vect2D& p3) {
  /*
   * Determines the orientation (clockwise, counterclockwise, colinear) of 3
   * points. The equation below computes the length of the cross product
   * of line (p1, p2) and (p2, p3), and from that we can infer whether the
   * rotation around it is clockwise, counterclockwise, or the lines are
   * colinear. See:
   * https://en.wikipedia.org/wiki/Cross_product#Computational_geometry
   */
  real val = (p2.y() - p1.y()) * (p3.x() - p2.x()) -
             (p3.y() - p2.y()) * (p2.x() - p1.x());
  if (eq(val, 0)) {
    return PointOrientation::COLINEAR;
  }
  return ((gt(val, 0)) ? PointOrientation::CLOCKWISE
                       : PointOrientation::COUNTERCLOCKWISE);
}

Vect2D toVect2D(const Direction& dir) { return Vect2D(dir.x(), dir.y()); }
Direction toDirection(const Vect2D& vect) {
  Direction yDirection = Direction::None(), xDirection = Direction::None();
  if (vect.x() > 0) {
    xDirection = Direction::Right();
  } else if (vect.x() < 0) {
    xDirection = Direction::Left();
  }

  if (vect.y() > 0) {
    yDirection = Direction::Up();
  } else if (vect.y() < 0) {
    yDirection = Direction::Down();
  }
  return yDirection + xDirection;
}

Vect2D closest(const Vect2D& origin, const Vect2D& vect1, const Vect2D& vect2) {
  return origin.distance(vect1) <= origin.distance(vect2) ? vect1 : vect2;
}
