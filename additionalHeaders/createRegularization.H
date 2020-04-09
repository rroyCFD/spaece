// RegularizationModel

RegularizationModel* RegModel;

// Check the convection-term-regularization on or off
bool regOn (spaece.dict().lookupOrDefault<bool>("regularizationOn", false));
Info << "regularizationOn: " << regOn << endl;

// Check the whether to set extrapolated-filtered fields to make divergence free
bool filterFieldDivFree(false);
if(regOn)
{
    //filterFieldDivFree = readBool(spaece.dict().lookup("filterFieldDivFree"));
    filterFieldDivFree =
            spaece.dict().lookupOrDefault<bool>("filterFieldDivFree", false);
    Info << "Extrapolated-filtered fields made divergence free: "
         << filterFieldDivFree << endl;
}


if(regOn)
{
    RegModel = new RegularizationModel(
                            pp, pRefCell, pRefValue, spaece.nNonOrthCorr());
    RegModel->setRegOn(regOn);
    RegModel->setFilterFieldsDivFree(filterFieldDivFree);
    // Info << "Regularization Object Constructor" << endl;
}
else
{
    delete RegModel;
}

//------------------------------------------------------------------------//