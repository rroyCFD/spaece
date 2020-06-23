{
    volVectorField HbyA(constrainHbyA(rAU*UEqn.H(), U, p));

    surfaceScalarField phiHbyA ("phiHbyA", fvc::flux(HbyA) );
    // + MRF.zeroFilter(rAUf*fvc::ddtCorr(U, phi))

    MRF.makeRelative(phiHbyA);

    // Update the pressure BCs to ensure flux consistency
    constrainPressure(p, U, phiHbyA, rAU, MRF);

    // Apply the same gradient to pp following the coresponding pressure BCs
    forAll(p.boundaryField(), patchi)
    {
        if(isType<fixedFluxPressureFvPatchScalarField>(p.boundaryField()[patchi]))
        {
            fixedFluxPressureFvPatchScalarField& pGradPatch =
                refCast<fixedFluxPressureFvPatchScalarField>
                    (p.boundaryFieldRef()[patchi]);

            fixedGradientFvPatchScalarField& ppGradPatch =
                refCast<fixedGradientFvPatchScalarField>
                    (pp.boundaryFieldRef()[patchi]);

            ppGradPatch.gradient() = pGradPatch.gradient();
        }
    }
}