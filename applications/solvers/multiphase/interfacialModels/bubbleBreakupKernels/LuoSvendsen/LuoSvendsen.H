/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2015-2017 Alberto Passalacqua
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is derivative work of OpenFOAM.

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

Class
    Foam::breakupKernels::LuoSvendsen

Description
    Turbulent breakup kernel supplemented for bubbles in turbulent
    flows.

    \f[
        K_b = Cb \epsilon_f^{1/3} \text{erfc}
            \left(
                \sqrt{
                    C_1 \frac{\sigma}{\rho_f \epsilon_f^{2/3} \xi^{5/3}}
                  + C_2 \frac{\mu_f}
                    {\sqrt{rho_f \rho_b} \epsilon_f^{1/3} \xi^{4/3}}
                }
            \right)
    \f]

    where

    \vartable
        \sigma      |  Surface tension
        \rho_f      |  Density of liquid phase [kg/m3]
        \rho_b      |  Density of bubble phase [kg/m3]
        \epsilon_f  |  Turbulent dissipation rate of liquid phase [m2/s3]
        \mu_f       |  Molecular dynamic iscosity of liquid phase [Pa s]
        \xi         |  Abscissa of bubble [m]
    \endvartable

    References
    \verbatim
        "Theoretical model for drop and bubble breakup in turbulent dispersions"
        H. Luo and H. F. Svendsen
        AIChE Journal
        Volume 42, Pages 1225-1233, 1996
    \endverbatim

SourceFiles
    LuoSvendsen.C

\*---------------------------------------------------------------------------*/

#ifndef LuoSvendsen_H
#define LuoSvendsen_H

#include "bubbleBreakupKernel.H"
#include "twoPhaseSystem.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{
namespace bubbleBreakupKernels
{

/*---------------------------------------------------------------------------*\
                        Class LuoSvendsen Declaration
\*---------------------------------------------------------------------------*/

class LuoSvendsen
:
    public bubbleBreakupKernel
{
    // Private data

        //- Refrence to two phase system
        const twoPhaseSystem& fluid_;

        // Model Coefficients
        dimensionedScalar Cf_;

        //- Turbulent dissipation rate
        volScalarField epsilonf_;

        //- Turbulent eddy size
        volScalarField de_;


public:

        //- Runtime type information
        TypeName("LuoSvendsen");


    // Constructors

        //- Construct from components
        LuoSvendsen
        (
            const dictionary& dict,
            const fvMesh& mesh
        );


    //- Destructor
    virtual ~LuoSvendsen();


    // Member Functions

        //- Update non-stored fields
        virtual void update();

        //- Breakup kernel
        virtual tmp<volScalarField> Kb(const label nodei) const;

        //- Breakup kernel for a cell
        virtual scalar Kb(const label celli, const label nodei) const;

};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace breakupKernels
} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
