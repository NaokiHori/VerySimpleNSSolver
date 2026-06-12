#if !defined(BOUNDARY_CONDITION_H)
#define BOUNDARY_CONDITION_H

#include "domain.h" // domain_t

#if !defined(X_PERIODIC)
extern int impose_boundary_condition_ux_x(
    const domain_t * const domain,
    double ** const ux
);
#endif

#if !defined(Y_PERIODIC)
extern int impose_boundary_condition_ux_y(
    const domain_t * const domain,
    double ** const ux
);
#endif

#if !defined(X_PERIODIC)
extern int impose_boundary_condition_uy_x(
    const domain_t * const domain,
    double ** const uy
);
#endif

#if !defined(Y_PERIODIC)
extern int impose_boundary_condition_uy_y(
    const domain_t * const domain,
    double ** const uy
);
#endif

#endif // BOUNDARY_CONDITION_H
