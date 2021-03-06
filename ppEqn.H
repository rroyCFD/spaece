volScalarField rAU(1.0/UEqn.A());
tUEqn.clear();

// RhieChow flux correction
if(RhieChow)
{
    tmp<surfaceVectorField> gradpDiff_f
    (
        (  (fvc::interpolate(fvc::grad(p)) & ed)
          - faceGradient.snGrad(p)
        ) * ed
    );

    phi =
        fvc::flux(U)
        + fvc::interpolate(rAU)* (gradpDiff_f() & mesh.Sf());

    gradpDiff_f.clear();
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

// Update the pressure BCs to ensure flux consistency
// applicable at fixedFlux type pressure boundaries
constrainPressure(p, U, phi, rAU, MRF);


// pressure corrector loop (with Non-orthogonal correction)
pp.primitiveFieldRef() = 0.0;
pp.correctBoundaryConditions();

while (spaece.correctNonOrthogonal())
{
    fvScalarMatrix ppEqn
    (
      fvm::laplacian(rAU, pp, "laplacian(p)") == (fvc::div(phi))
    );

    // no correction to reference cell pressure
    scalar ppRefValue = pRefValue - getRefCellValue(p, pRefCell);
    ppEqn.setReference(pRefCell, ppRefValue);

    ppEqn.solve(mesh.solver(pp.select(spaece.finalInnerIter())));

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

U -= rAU*fvc::grad(pp);
U.correctBoundaryConditions();
fvOptions.correct(U);

p += pp;
p.correctBoundaryConditions();

// Info << "fields updated" << endl;