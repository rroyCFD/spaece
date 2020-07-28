// Rhie-Chow correction

// Check for the RhieChow correction
bool RhieChow (spaece.dict().lookupOrDefault<bool>("RhieChow", true));
Info << "RhieChow: " << RhieChow << endl;

// Check for the RhieChow-ddt correction
bool ddtCorr (spaece.dict().lookupOrDefault<bool>("ddtCorr", false));
Info << "ddtCorr: " << ddtCorr << endl;

// cell-centers connecting vector
const surfaceVectorField ed = mesh.delta()()/mag(mesh.delta()());

// surface normal gradient object
Foam::fv::orthogonalSnGrad<scalar> faceGradient(mesh);