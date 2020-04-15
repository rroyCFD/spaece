// kinetic energy analysis output to file
if(KEAnalysis)
{
     Info << "Time = " << runTime.elapsedCpuTime() << " s" << endl;
     KE->analyzeKEBalance();
     KE->getAddtionalKETerms();
     KE->writeAvgValues();
}