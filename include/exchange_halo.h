#if !defined(EXCHANGE_HALO_H)
#define EXCHANGE_HALO_H

#include "domain.h" // domain_t

#if defined(X_PERIODIC)
extern int exchange_halo_x(
    const domain_t * const domain,
    double ** const array
);
#endif

#if defined(Y_PERIODIC)
extern int exchange_halo_y(
    const domain_t * const domain,
    double ** const array
);
#endif

#endif // EXCHANGE_HALO_H
