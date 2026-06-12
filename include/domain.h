#if !defined(DOMAIN_H)
#define DOMAIN_H

#include <stddef.h> // size_t

// x is periodic when defined; otherwise wall-bounded
#define X_PERIODIC
// y is periodic when defined; otherwise wall-bounded
// #define Y_PERIODIC

extern const size_t ux_imin;
extern const size_t uy_jmin;

typedef struct {
  double lx;
  double ly;
  size_t nx;
  size_t ny;
  double dx;
  double dy;
} domain_t;

extern int domain_init(
    domain_t * const domain
);

#endif // DOMAIN_H
