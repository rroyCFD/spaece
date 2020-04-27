### fvScheme
	
Interpolation shall be midPoint for divergence, gradient and Laplace schemes.
	
	gradSchemes
	{
	    default         Gauss midPoint;
	}

	divSchemes
	{
	    default         Gauss midPoint;
	}

	laplacianSchemes
	{
	    default         Gauss midPoint orthogonal; // corrected;
	}

	interpolationSchemes
	{
	    default         midPoint;
	}

	snGradSchemes
	{
	 	default         orthogonal; // corrected;
	}

	fluxRequired
	{
	    default         no;
	    pp;
	}


### fvSolution

Momentum solve linear system is symmetric

	"U|UFinal"
	{
	  solver          PCG;
	  preconditioner  DIC;
	  tolerance       1e-10;
	  relTol          0;
	  minIter         1;
	}

SPAeCE control parameters

	SPAeCE
	{
	    // pRefCell                0;
	    pRefPoint               (0 $piBy2 0);
	    pRefValue                0;

	    nNonOrthogonalCorrectors 0;
	    
	    RhieChow                false;
	    
	    regularizationOn        false;
	    filterFieldDivFree      false;
	    
	    KEAnalysis              false;
	}

In case of advection term regularization


	regularization
	{
	    regOrder        C6; // C4 C2
	    filter          polyLaplace;

	    // epsilon (filter to grid spacing ratio) 3
	    d1              0.375; // 3/8
	    d2              0.0375; // 3/80

	    // epsilon (filter to grid spacing ratio) 2
	    // d1          0.16666667; // 1/6
	    // d2          0.00416667; //1/240

	}

	regResidual
	{
	    residualOrder   C6; // C4 C2
	    filter          polyLaplaceResidual;
	    d1              0.375;
	    d2              0.0375;
	}