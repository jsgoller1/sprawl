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

/*
 * TODO: We should probably introduce a Line class, and reuse lineContainsPoint
 * in intervalsOverlap
 */
bool lineContainsPoint(const shared_ptr<Vect2D> lineStart,
                       const shared_ptr<Vect2D> lineEnd,
                       const shared_ptr<Vect2D> point) {
  /*
   * A 2D point falls on a 2D line if:
   * - The point's x falls between the start's x and end's x (and same for y)
   * - The slope between the start and the point is the same as the slope
   * between the start and end
   */
  if (!(rangeContainsVal(lineStart->x, lineEnd->x, point->x) &&
        rangeContainsVal(lineStart->y, lineEnd->y, point->y))) {
    return false;
  }
  PositionUnit lineDX = lineStart->x - lineEnd->x;
  PositionUnit pointDX = lineStart->x - point->x;
  PositionUnit lineDY = lineStart->y - lineEnd->y;
  PositionUnit pointDY = lineStart->y - point->y;
  return eq(lineDX, pointDX) && eq(lineDY, pointDY);
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

bool lineIntersectsBox(const shared_ptr<Vect2D> lineStart,
                       const shared_ptr<Vect2D> lineEnd,
                       const shared_ptr<Box> box) {}
