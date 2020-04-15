/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    spaeceFoam

Description
    Transient solver for incompressible, turbulent flow, using the SPAeCE
    algorithm.

    Sub-models include:
    - turbulence modelling, i.e. laminar, RAS or LES
    - run-time selectable MRF and finite volume options, e.g. explicit porosity

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "singlePhaseTransportModel.H"
#include "turbulentTransportModel.H"
#include "spaeceControl.H"
#include "fvOptions.H"
#include "orthogonalSnGrad.H"


#include "RegularizationModel.H"

#include "TaylorGreenVortex.H"
#include "TaylorGreenVortex2D.H"
#include "TaylorGreenVortex3D.H"
// * * * * * * * * * * * * * * * 
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createSPAeCEControl.H"
    #include "createFields.H"
    #include "initContinuityErrs.H"

    #include "postProcess.H"

    #include "createRhieChow.H"

    #include "createRegularization.H"

    #include "createKineticEnergy.H"
    
    #include "createTGV.H"
    #include "writeTGV.H"

    turbulence->validate();

    Info<< "\nStarting time loop\n" << endl;

    while (runTime.loop())
    {
        Info<< "Time = " << runTime.timeName() << nl << endl;

        #include "CourantNo.H"

        #include "extrapolateFields.H"

        // Pressure-velocity corrector
        while (spaece.correct())
        {
            #include "UEqn.H"

            #include "ppEqn.H"
        }

        laminarTransport.correct();
        turbulence->correct();

        runTime.write();

        #include "writeTGV.H"

        Info<< "ExecutionTime = " << runTime.elapsedCpuTime() << " s"
            << "  ClockTime = " << runTime.elapsedClockTime() << " s"
            << nl << endl;
    }

    Info<< "End\n" << endl;

    #include "clearRegularization.H"
    
    #include "clearTGV.H"
    return 0;
}


// ************************************************************************* //
