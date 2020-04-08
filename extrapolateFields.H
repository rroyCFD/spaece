// extrapolate fields to next-time step to obtain a better initial condition
p = ((1+kappa) * p.oldTime() - kappa * p.oldTime().oldTime());
p.correctBoundaryConditions();

// Update U and phi with their respective extrapolated value
phi = ((1+kappa) * phi.oldTime() - kappa * phi.oldTime().oldTime());

U = ((1+kappa) * U.oldTime() - kappa * U.oldTime().oldTime());
// U.correctBoundaryConditions(); updated at UEqn matrix formation

// MRF.correctBoundaryVelocity(U);
