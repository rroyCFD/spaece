// CrankNicolson split of the diffusion (laplacian) term
tmp<fvVectorMatrix> tUEqn
(
      fvm::ddt(U)
    + RegModel->getConvectionTerm(phi, U) // regularized 
    // CrankNicolson split for advection is dissipative
    // + 0.5*(fvm::div(phi,U) + fvc::div(phi,U)) 
    - 0.5*(
          fvm::laplacian(turbulence->nuEff(), U) 
        + fvc::laplacian(turbulence->nuEff(), U)
    )
    - fvc::div(turbulence->nuEff() * dev2(T(fvc::grad(U))))
    ==
    - fvc::grad(p) 
    + fvOptions(U)
);
fvVectorMatrix& UEqn = tUEqn.ref();

UEqn.relax();

fvOptions.constrain(UEqn);

solve(UEqn);
// To track residual; use UFinal for last-leg of the loop
// solve(UEqn, mesh.solver(U.select(spaece.finalSPAeCEIter())));

// Can create negative driving presssure grad when momentum is over-predicted
// fvOptions.correct(U);