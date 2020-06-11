// RegularizationModel
RegularizationModel* RegModel;

// Check the convection-term-regularization on or off
bool regOn (spaece.dict().lookupOrDefault<bool>("regularizationOn", false));
Info << "regularizationOn: " << regOn << endl;

// output file to write regularized advection KE 
autoPtr<OFstream> regAdvKEFile;

if(regOn)
{
    RegModel = new RegularizationModel(
                            pp, pRefCell, pRefValue, spaece.nNonOrthCorr());
    RegModel->setRegOn(regOn);

    //- write regularized Advection KE when KEAnalysis is True
    if(KEAnalysis)
    {
        #include "createRegularizedAdvectionKE.H"
        #include "writeRegularizedAdvectionKE.H"
    }    
}
else
{
    delete RegModel;
    regAdvKEFile.clear();
}
//------------------------------------------------------------------------//