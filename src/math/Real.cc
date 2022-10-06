#include "Real.hh"

// TODO: Floating point comparison is hard; here, we're just doing
// a margin-of-error test and calling it a day. Followups:
// - CS:APP (Bryant et al), sec 3.11
// - https://floating-point-gui.de/errors/comparison/
bool eq(const real& real1, const real& real2) {
  real diff = real1 - real2;
  return ((-FLOAT_EQ_ACCEPTABLE_MARGIN_OF_ERROR < diff) &&
          (diff < FLOAT_EQ_ACCEPTABLE_MARGIN_OF_ERROR));
}
bool lt(const real& real1, const real& real2) {
  return real1 < real2 && !eq(real1, real2);
}
bool gt(const real& real1, const real& real2) {
  return real1 > real2 && !eq(real1, real2);
}
bool neq(const real& real1, const real& real2) { return !eq(real1, real2); }
bool lte(const real& real1, const real& real2) {
  return lt(real1, real2) || eq(real1, real2);
}
bool gte(const real& real1, const real& real2) {
  return gt(real1, real2) || eq(real1, real2);
}
