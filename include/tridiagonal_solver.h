#if !defined(TRIDIAGONAL_SOLVER_H)
#define TRIDIAGONAL_SOLVER_H

#include <stddef.h> // size_t
#include <stdbool.h> // bool

typedef struct tridiagonal_solver_internal_t tridiagonal_solver_internal_t;

typedef struct {
  // size of linear system
  size_t nitems;
  // repeat several times
  size_t repeat_for;
  bool is_periodic;
  // for internal use, opaque pointer
  tridiagonal_solver_internal_t * internal;
} tridiagonal_solver_plan_t;

extern int tridiagonal_solver_init_plan(
    const size_t nitems,
    const size_t repeat_for,
    const bool is_periodic,
    tridiagonal_solver_plan_t ** const tridiagonal_solver_plan
);

extern int tridiagonal_solver_exec(
    tridiagonal_solver_plan_t * const tridiagonal_solver_plan,
    // tri-diagonal matrix, lower, center, upper-diagonals
    const double * const l,
    const double * const c,
    const double * const u,
    // offset for center-diagonal components, can vary for each repeat
    const double * const c_offsets,
    // input and output
    double * const q
);

extern int tridiagonal_solver_destroy_plan(
    tridiagonal_solver_plan_t ** const tridiagonal_solver_plan
);

#endif // TRIDIAGONAL_SOLVER_H
