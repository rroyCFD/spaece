// CrankNicolson split of the diffusion (laplacian) term
tmp<fvVectorMatrix> tUEqn
(
      fvm::ddt(U)
    + fvc::div(phi,U) // advection explicit is necessary for KE conservation
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

if(regOn)
{
    // subtract advection correction to attenuate high frequency modes
    solve
    (
        (UEqn == RegModel->convectionResidual(phi, U) ), 
        mesh.solver(U.select(spaece.finalSPAeCEIter()))
    );
}
else
{
	// Use UFinal for last-leg of the loop
	solve(UEqn, mesh.solver(U.select(spaece.finalSPAeCEIter())));
}

// can create negative driving presssure grad when momentum is over-predicted
// fvOptions.correct(U);