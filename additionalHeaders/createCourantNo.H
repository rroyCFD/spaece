/*---------------------------------------------------------------------------*\
Global
    CourantNo

Description
    Calculates and outputs the mean and maximum Courant Numbers.

\*---------------------------------------------------------------------------*/
scalar CoNum = 0.0;
scalar meanCoNum = 0.0;

fileName constantPath(runTime.constantPath());
if(Pstream::parRun())
{
    constantPath = runTime.path()+"/../constant/";
    // Info << "Constant dictionary path: " << constantPath << endl;
}

IOdictionary CFL
(
    IOobject
    (
        "CFL",
        constantPath,
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    )
);

// save to the CFL dict in constant directory
CFL.set<scalar>("maxCo", CoNum);

// Info << U.db().sortedNames() << endl;

// scalar test(CFL.lookupOrDefault<scalar>("maxCo", -1));
// Info << "***test CFL: " << test << endl;
// ************************************************************************* //
