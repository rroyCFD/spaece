// fvVectorMatrix UEqn
tmp<fvVectorMatrix> tUEqn
(
      fvm::ddt(U)
    + MRF.DDt(U)
    + (fvc::div(phi,U) - U * fvc::div(phi)) // advection explict
    // + turbulence->divDevReff(U)
    - fvm::laplacian(turbulence->nuEff(), U)
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

fvOptions.correct(U);