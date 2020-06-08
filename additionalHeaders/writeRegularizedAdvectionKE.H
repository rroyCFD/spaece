if(KEAnalysis && regOn)
{
    tmp<volScalarField> tRegAdvKE
    (
        new volScalarField
        (
            IOobject
            (
                "regAdvKE",
                U.instance(),
                mesh,
                IOobject::NO_READ,
                IOobject::NO_WRITE
            ),
            (U & RegModel->convectionResidual(phi, U))
        )
    );
    volScalarField& regAdvKE = tRegAdvKE.ref();
    regAdvKE.write(runTime.outputTime());

    // volume weighted average
    dimensionedScalar avgRegAdvKE = regAdvKE.weightedAverage(mesh.V());
    Info << "\tavg of regularized advection KE: "<< avgRegAdvKE.value() << endl;

    if(!(Pstream::parRun() && !(Pstream::master())))
    {
        regAdvKEFile() << runTime.value() << tab << avgRegAdvKE.value() << endl;
    }
}