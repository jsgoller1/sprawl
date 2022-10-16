#include "Real.hh"
#include "Types.hh"
#include "Vect2D.hh"

class Line {
 public:
  Line(const shared_ptr<Vect2D> p1, const shared_ptr<Vect2D> p2);
  Line(const shared_ptr<const Vect2D> p1, const shared_ptr<const Vect2D> p2);
  Line(const shared_ptr<Line> line);

  shared_ptr<Vect2D> getSlope() const;
  shared_ptr<pair<shared_ptr<Vect2D>, shared_ptr<Vect2D>>> getPoints() const;
  shared_ptr<Vect2D> getLength() const;

 private:
  Line() = delete;
  shared_ptr<const Vect2D> slope;
  shared_ptr<const Vect2D> p1;
  shared_ptr<const Vect2D> p2;
};
