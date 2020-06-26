// fvVectorMatrix *UEqnPtr;

// if(regOn)
// {
//     UEqnPtr = new fvVectorMatrix
//     (
//           fvm::ddt(U)
//         + RegModel->getConvectionTerm(phi, U) // regularized 
//         // CrankNicolson split for advection is dissipative
//         // + 0.5*(fvm::div(phi,U) + fvc::div(phi,U)) 
//         - 0.5*(
//               fvm::laplacian(turbulence->nuEff(), U) 
//             + fvc::laplacian(turbulence->nuEff(), U)
//         )
//         - fvc::div(turbulence->nuEff() * dev2(T(fvc::grad(U))))
//         ==
//           fvOptions(U)
//     );
// } 
// else
// {
//     UEqnPtr = new fvVectorMatrix
//     (
//           fvm::ddt(U)
//         // + fvc::div(phi,U)
//         + 0.5*(fvm::div(phi,U) + fvc::div(phi.oldTime(), U.oldTime())) // classical CrankNicolson scheme
//         - 0.5*(
//               fvm::laplacian(turbulence->nuEff(), U) 
//             + fvc::laplacian(turbulence->nuEff(), U.oldTime()) // classical CrankNicolson scheme
//         )
//         - fvc::div(turbulence->nuEff() * dev2(T(fvc::grad(U))))
//         ==
//           fvOptions(U)
//     );
// }

// fvVectorMatrix& UEqn = *UEqnPtr;

tmp<fvVectorMatrix> tUEqn
(
    fvm::ddt(U) // shall be implicit Euler
    // classical CrankNicolson scheme
    + 0.5*(
            fvm::div(phi,U) 
          + fvc::div(phi.oldTime(), U.oldTime())
          
          // written for eddy viscosity as it's easy to split
          - fvm::laplacian(turbulence->nuEff(), U) 
          - fvc::laplacian(turbulence->nuEff(), U.oldTime())
    )
    - fvc::div(turbulence->nuEff() * dev2(T(fvc::grad(U))))
    ==
    fvOptions(U)
);
fvVectorMatrix& UEqn = tUEqn.ref();

UEqn.relax();

fvOptions.constrain(UEqn);

if(regOn)
{
    // - Only applicable for A6
    //   Extrapolated or updated phi and U values are used for regularization
    solve(UEqn == - fvc::grad(p) + RegModel->convectionResidual(phi,U));
}
else
{
    solve(UEqn == - fvc::grad(p) );
}

// To track residual; use UFinal for last-leg of the loop
// solve((UEqn == - fvc::grad(p) ), mesh.solver(U.select(spaece.finalSPAeCEIter())));

// Can create negative driving presssure grad when momentum is over-predicted
// fvOptions.correct(U);