## Application : Symmetry Preserving, Advection explicit, Conservation of Energy (SPAeCE) Foam

### Author:
- Rajib Roy
- University of Wyoming
- rroy@uwyo.edu, roy.rajib@live.com

### Description
Transient solver for incompressible, turbulent flow, using the symmetry preserving discrete spatial operators and explicit treatment of linearized advection term leads to conserves kinetic energy. Algorithm is implemented following the research work of:

        Trias, F. X., Lehmkuhl, O., Oliva, A., Pérez-Segarra, C. D., & Verstappen, R. W. C. P. (2014).
        Symmetry-preserving discretization of Navier–Stokes equations on collocated unstructured grids.
        Journal of Computational Physics, 258, 246–267. https://doi.org/10.1016/j.jcp.2013.10.031

        Sanderse, B. (2013). Energy-conserving runge-kutta methods for the incompressible navier-stokes equations. Journal of Computational Physics, 233(1), 100–131. https://doi.org/10.1016/j.jcp.2012.07.039

        Mahesh, K., Constantinescu, G., & Moin, P. (2003). A numerical method for large-eddy simulation in complex geometries. In Computational Fluid and Solid Mechanics 2003 (Vol. 197, pp. 23–30). https://doi.org/10.1016/B978-008044046-0.50009-9

        Verstappen, R. W. C. P., & Veldman, A. E. P. (2003). Symmetry-preserving discretization of turbulent flow. Journal of Computational Physics, 187(1), 343–368. https://doi.org/10.1016/S0021-9991(03)00126-8

Sub-models include:

* turbulence modelling, i.e. laminar, RAS or LES
* run-time selectable MRF and finite volume options such as mean velocity, etc.


### Disclaiimer:

This application is built based on [OpenFOAM version-6](https://openfoam.org/release/6/). Please read the _About OpenFOAM_ section to learn more on OpenFOAM.

The application is free to use. The author neither provide any warranty nor shall be liable for any damage incurred from this application.



#### About OpenFOAM

OpenFOAM is the leading free, open source software for computational fluid dynamics (CFD), owned by the OpenFOAM Foundation and distributed exclusively under the [General Public Licence (GPL)](http://www.gnu.org/copyleft/gpl.html). The GPL gives users the freedom to modify and redistribute the software and a guarantee of continued free use, within the terms of the licence. To learn more visit [https://openfoam.org/](https://openfoam.org/)
