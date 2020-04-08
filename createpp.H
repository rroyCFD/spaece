//----------------------------------------------------------------------------//
Info << "\nCreating pressure-coorection field pp" << endl;
const wordList pbt = p.boundaryField().types();

// prepare the boundary condition types for pressure-correction field
// if pressure BC is a fixed value type, pp is fixedValue, uniform zero
// if preseser BC is a fixed Gradient type, pp is zeroGradient
wordList ppbt = pbt;
/*
forAll(ppbt, b)
{
    if(ppbt[b] == "timeVaryingMappedFixedValue")
    {
        ppbt[b] = "fixedValue";
    }
}
*/
forAll(p.boundaryField(), patchi)
{
    if (isType<fixedValueFvPatchScalarField>(p.boundaryField()[patchi]))
    {
        ppbt[patchi] = "fixedValue";
    } 
    else if (isType<fixedGradientFvPatchScalarField>(p.boundaryField()[patchi]))
    {
        ppbt[patchi] = "zeroGradient";
    }
}
// need to create a corresponding mixed BC for pp;

volScalarField pp
(
    IOobject
    (

        "pp",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT, // NO_READ,
        IOobject::AUTO_WRITE // NO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", p.dimensions(), 0.0),
    ppbt
);

Info << "Pressure correction field boundary types:"
     << pp.boundaryField().types() << endl;


// Set pp boundary values
// boundaryFieldRef() return a (non-const) reference to the boundary field
// refCast converts the generic boundary field to a fixedValueFvPatchScalarField
forAll(pp.boundaryField(), patchi)
{
    if (isType<fixedValueFvPatchScalarField>(pp.boundaryField()[patchi]))
    {
        fixedValueFvPatchScalarField& ppbound =
           refCast<fixedValueFvPatchScalarField>(pp.boundaryFieldRef()[patchi]);

        ppbound == scalarField(ppbound.size(),0.0);
    }
}