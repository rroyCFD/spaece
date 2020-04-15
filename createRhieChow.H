// Rhie-Chow correction

// Check for the RhieChow correction
bool RhieChow (spaece.dict().lookupOrDefault<bool>("RhieChow", true));
Info << "RhieChow: " << RhieChow << endl;

// cell-centers connecting vector
const surfaceVectorField ed = mesh.delta()()/mag(mesh.delta()());

// surface normal gradient object
Foam::fv::orthogonalSnGrad<scalar> faceGradient(mesh);