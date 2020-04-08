Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"

singlePhaseTransportModel laminarTransport(U, phi);

autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);

#include "createMRF.H"
#include "createFvOptions.H"


Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

label pRefCell = 0;
scalar pRefValue = 0.0;
const bool pRefOn(setRefCell(p, spaece.dict(), pRefCell, pRefValue));
if(pRefOn)
{
    #include "adjustP.H"
}

// create/read the pressure correction field
#include "createpp.H"
mesh.setFluxRequired(pp.name());

// Read solution control parameters
const scalar kappa(spaece.dict().lookupOrDefault<scalar>("kappa", 0.50));
Info << "Extrapolation coeff. kappa: " << kappa << endl;

// Check for the RhieChow correction
bool RhieChow (spaece.dict().lookupOrDefault<bool>("RhieChow", true));
Info << "RhieChow: " << RhieChow << endl;