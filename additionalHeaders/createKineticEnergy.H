// Declare a Kinetic Energy term-by-term analysis object (if present)

kineticEnergyAnalysis* KE;

// Check for kinetic energy analysis switch
bool KEAnalysis (spaece.dict().lookupOrDefault<bool>("KEAnalysis", false));
Info << "kinetic energy analysis: " << KEAnalysis << endl;

if(KEAnalysis)
{
    KE = new kineticEnergyAnalysis(U, phi, p);
    KE->setPropertiesOutput();
    KE->analyzeKEBalance();
    KE->getAddtionalKETerms();
    KE->writeAvgValues();
}
else
{
    delete KE;
}
//------------------------------------------------------------------------//