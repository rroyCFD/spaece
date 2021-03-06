// Declare a TGV object pointer and assign if TGV present

TaylorGreenVortex* TGVPtr(nullptr);
bool TGVOn (false);

fileName dictPath(runTime.constantPath());
if(Pstream::parRun())
{
    dictPath = runTime.path()+"/../constant/";
    Info << "Constant dictionary path: " << dictPath << endl;
}

// Check for Taylor Green Vortex
IOobject TGVPropertiesHeader
(
    "TaylorGreenVortexProperties",
    dictPath, // runTime.constant(),
    mesh,
    IOobject::NO_READ
);

// debug: decomposed case execution: points to processor0/constant folder
// Info << TGVPropertiesHeader.path() << endl;
// Info << TGVPropertiesHeader.rootPath() << endl;
// Info << TGVPropertiesHeader.objectPath() << endl;

if(TGVPropertiesHeader.typeHeaderOk<dictionary>(true))
{
    TGVOn = true;

    IOdictionary TGVProperties_
    (
        IOobject
        (
            "TaylorGreenVortexProperties",
            dictPath,
            mesh,
            IOobject::MUST_READ,
            IOobject::NO_WRITE
        )
    );

    const word dimension_(TGVProperties_.lookup("dimension"));
    // dimension_ = (TGVProperties_.lookupOrDefault<word>("dimension", "1D"))

    if(dimension_ == "2D")
    {
         TGVPtr = new TaylorGreenVortex2D(U, phi, p, pRefCell);
    }
    else if(dimension_ == "3D")
    {
        TGVPtr = new TaylorGreenVortex3D(U, phi, p);
    }
    else
    {
        FatalErrorInFunction
            << "Taylor-Green Vortex dimension " << dimension_ << " is invalid!"
            << "\n Options are 2D or 3D." << abort(FatalError);
    }


    // Initialize the fields if required
    Switch initialize_(false);
    initialize_.readIfPresent("initialize", TGVProperties_);
    Info << "TGV initialize: " << initialize_ << endl;

    if(initialize_ && runTime.startTime().value() == 0)
    {
        TGVPtr->setInitialFieldsAsAnalytical(U, phi, p);
        U.write();
        phi.write();

        if(pRefOn)
        {
            if( mag(getRefCellValue(p, pRefCell) - pRefValue) > SMALL)
            {
                dimensionedScalar pCorr
                (
                    "pCorr",
                    p.dimensions(),
                    (getRefCellValue(p, pRefCell) - pRefValue)
                );
                p -= pCorr;
                p.correctBoundaryConditions();
            }
        }
        p.write();
    }
}
else
{
    delete TGVPtr;
}
//------------------------------------------------------------------------//