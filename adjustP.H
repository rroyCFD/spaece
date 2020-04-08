// adjust pressure field to achieve reference pressure at ref cell
// this avoids large pressure iterations a first time step
{
    Info << "pRefCell: " << pRefCell << "\tpRefValue: " << pRefValue << tab
    << "initial   field ref value: " << getRefCellValue(p, pRefCell) << endl;

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

        Info << "pRefCell: " << pRefCell << "\tpRefValue: " << pRefValue << tab
        << "corrected field ref value: " << getRefCellValue(p, pRefCell)<< endl;
    }
}