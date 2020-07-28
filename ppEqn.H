volScalarField rAU(1.0/UEqn.A());
surfaceScalarField rAUf = fvc::interpolate(rAU);

// RhieChow flux correction
if(RhieChow & ddtCorr)
{
    tmp<surfaceScalarField> gradpDiff_f
    (
        (((fvc::interpolate(fvc::grad(p)) & ed) - faceGradient.snGrad(p)) * ed)
        & mesh.Sf()
    );
    // ddt correction involves U.oldTime and phi.oldTime;
    // without it, small time-step may result in ocillatory behaviour
    phi = fvc::flux(U) + rAUf * (gradpDiff_f() + fvc::ddtCorr(U, phi));
}
else if(RhieChow)
{
    tmp<surfaceScalarField> gradpDiff_f
    (
        (((fvc::interpolate(fvc::grad(p)) & ed) - faceGradient.snGrad(p)) * ed)
        & mesh.Sf()
    );
    
    phi = fvc::flux(U) + rAUf * gradpDiff_f();
    gradpDiff_f.clear();
}
else if (ddtCorr)
{
    phi = fvc::flux(U) + rAUf * fvc::ddtCorr(U, phi);
}
else
{
    phi = fvc::flux(U);
}

// ddt correction not applied as it was too diffusive
// + MRF.zeroFilter(fvc::interpolate(rAU)*fvc::ddtCorr(U, phi))

// MRF.makeRelative(phi);

// For cases which do not have a pressure boundary.
// Adjust the balance of fluxes to obey continuity.
// normalizes flux based on mass in vs mass out balance
adjustPhi(phi, U, p);

// SIMPLE-consistent like correction to diagonal coefficients
tmp<volScalarField> rAtU(rAU);
if (spaece.consistent())
{
    rAtU = 1.0/(1.0/rAU - UEqn.H1());
}

// rAtU = dt when advection (implicit) term is skew-symmetric and Laplace term is symmetric

// Update the pressure BCs to ensure flux consistency
// applicable at fixedFlux type pressure boundaries
// update fixedFluxPressure BC for p and copy gradient to pp
if(fixedFluxBC)
{
    #include "updatefixedFluxPressureGrad.H"
}

tUEqn.clear();
// delete UEqnPtr;

// pressure corrector loop (with Non-orthogonal correction)
// - pp shall not set to zero and pp at old time is a better approximation than
//   0; reduced number of pressure corrections ~25% (from 14 to 11)
// pp.primitiveFieldRef() = 0.0;
// pp.correctBoundaryConditions();

while (spaece.correctNonOrthogonal())
{
    fvScalarMatrix ppEqn
    (
      fvm::laplacian(rAtU(), pp, "laplacian(p)") == (fvc::div(phi))
    );

    // no correction to reference cell pressure
    scalar ppRefValue = pRefValue - getRefCellValue(p, pRefCell);
    ppEqn.setReference(pRefCell, ppRefValue);

    // ppEqn.solve(mesh.solver(pp.select(spaece.finalInnerIter())));
    // nCorrectors input is ignored! forced to 1
    ppEqn.solve(mesh.solver(pp.select(spaece.finalNonOrthogonalIter())));

    if (spaece.finalNonOrthogonalIter())
    {
        phi -= ppEqn.flux();
    }
}

// calculate continuity error after final iteration
if(spaece.finalSPAeCEIter())
{
    #include "continuityErrs.H"
}

U -= rAtU()*fvc::grad(pp);
U.correctBoundaryConditions();
fvOptions.correct(U);

p += pp;
p.correctBoundaryConditions();

// Info << "fields updated" << endl;

// pp shall not set ot zero; see explanantion above
// // set pressure correction to zero; reduce memory overhead
// pp.primitiveFieldRef() = 0.0;
