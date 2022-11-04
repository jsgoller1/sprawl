#include "Line.hh"

Line::Line(const Vect2D& start, const Vect2D& end) : _start(start), _end(end) {}
Line::Line(const Line& line) : _start(line._start), _end(line._end) {}

Vect2D Line::start() const { return this->_start; }
Vect2D Line::end() const { return this->_start; }

real Line::slope() const {
  /*
   * Calculates rise-over-run slope of the line. IMPORTANT: this function is
   * generally meant for use in geometry-related testing and ignores the
   * intent in specifying which points are the "start" and "end" points of the
   * line; it determines the slope between the leftmost point and the
   * rightmost point. If you are using Line to think about position change
   * from the start point to the end point, you probably want to use
   * displacement() instead.
   */
  Vect2D p1 = (this->_start.x() <= this->_end.x()) ? this->_start : this->_end;
  Vect2D p2 = ((p1 == this->_start) ? this->_end : this->_start);
  return (p1.y() - p2.y()) / (p1.x() - p2.x());
}

real Line::length() const {
  /*
   * Calculates the Euclidean distance between the start and end points of the
   * line.
   */
  return this->_start.distance(this->_end);
}

Vect2D Line::displacement() const {
  /*
   * Calculates the position delta from the start point to the end point of
   * the line.
   */
  return this->_end - this->_start;
}

bool Line::intersects(const Vect2D& point) const {
  /*
   * A 2D point falls on a 2D line if:
   * - The point's x falls between the start's x and end's x (and same for y)
   * - The slope between the start and the point is the same as the slope
   * between the start and end
   */
  if (!(rangeContainsVal(this->_start.x(), this->_end.x(), point.x()) &&
        rangeContainsVal(this->_start.y(), this->_end.y(), point.y()))) {
    return false;
  }
  return eq(Line(this->_start, point).slope(), this->slope());
}

bool Line::intersects(const Line& line) const {
  /*
   * Line intersection can be tested by looking at the orientation of triplets
   * of the points of each line. If all points are colinear, then the lines
   * can only intersect by overlapping. Otherwise, the lines only intersect if
   * the orientations all differ.
   *
   * References:
   * - https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
   * - https://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
   */
  PointOrientation orientation1 =
                       getOrientation(this->_start, this->_end, line.start()),
                   orientation2 =
                       getOrientation(this->_start, this->_end, line.end()),
                   orientation3 =
                       getOrientation(line.start(), line.end(), this->_start),
                   orientation4 =
                       getOrientation(line.start(), line.end(), this->_end);

  if (orientation1 | orientation2 | orientation3 |
      orientation4 == PointOrientation::COLINEAR) {
    return intervalsOverlap(this->_start.x(), this->_end.x(), line.start().x(),
                            line.end().x()) &&
           intervalsOverlap(this->_start.y(), this->_end.y(), line.start().y(),
                            line.end().y());
  }
  return (orientation1 != orientation2) && (orientation3 != orientation4);
}
