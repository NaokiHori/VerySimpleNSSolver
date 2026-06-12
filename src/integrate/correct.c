#include "logger.h"
#include "exchange_halo.h"
#include "./correct.h"

static int correct_ux(
    const domain_t * const domain,
    flow_field_t * const flow_field,
    const flow_solver_t * const flow_solver,
    const double dt
) {
  const size_t nx = domain->nx;
  const size_t ny = domain->ny;
  const double dx = domain->dx;
  double * const * const psi = flow_solver->psi;
  double ** const ux = flow_field->ux;
#pragma omp parallel for
  for (size_t j = 1; j <= ny; j++) {
    for (size_t i = ux_imin; i <= nx; i++) {
      ux[j][i] -= dt / dx * (
          - psi[j    ][i - 1]
          + psi[j    ][i    ]
      );
    }
  }
#if defined(X_PERIODIC)
  if (0 != exchange_halo_x(domain, ux)) {
    goto abort;
  }
#endif
#if defined(Y_PERIODIC)
  if (0 != exchange_halo_y(domain, ux)) {
    goto abort;
  }
#endif
  return 0;
#if defined(X_PERIODIC) || defined(Y_PERIODIC)
abort:
  return 1;
#endif
}

static int correct_uy(
    const domain_t * const domain,
    flow_field_t * const flow_field,
    const flow_solver_t * const flow_solver,
    const double dt
) {
  const size_t nx = domain->nx;
  const size_t ny = domain->ny;
  const double dy = domain->dy;
  double * const * const psi = flow_solver->psi;
  double ** const uy = flow_field->uy;
#pragma omp parallel for
  for (size_t j = uy_jmin; j <= ny; j++) {
    for (size_t i = 1; i <= nx; i++) {
      uy[j][i] -= dt / dy * (
          - psi[j - 1][i    ]
          + psi[j    ][i    ]
      );
    }
  }
#if defined(X_PERIODIC)
  if (0 != exchange_halo_x(domain, uy)) {
    goto abort;
  }
#endif
#if defined(Y_PERIODIC)
  if (0 != exchange_halo_y(domain, uy)) {
    goto abort;
  }
#endif
  return 0;
#if defined(X_PERIODIC) || defined(Y_PERIODIC)
abort:
  return 1;
#endif
}

int correct(
    const domain_t * const domain,
    flow_field_t * const flow_field,
    const flow_solver_t * const flow_solver,
    const double dt
) {
  if (0 != correct_ux(domain, flow_field, flow_solver, dt)) {
    LOGGER_FAILURE("failed to correct uy");
    goto abort;
  }
  if (0 != correct_uy(domain, flow_field, flow_solver, dt)) {
    LOGGER_FAILURE("failed to correct uy");
    goto abort;
  }
  return 0;
abort:
  LOGGER_FAILURE("failed to correct velocity field");
  return 1;
}

