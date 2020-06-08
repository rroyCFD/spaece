if(Pstream::master())
{
	// create output file
	fileName outputDir;
	

	if(Pstream::parRun())
	{
	    outputDir = runTime.path()/"../postProcessing";
	}
	else
	{
	    outputDir = runTime.path()/"postProcessing";
	}

	if (!isDir(outputDir))
	{
	    mkDir(outputDir);
	}

	fileName outFilePath(
		outputDir/("regularizedAdvectionKE.dat_"+runTime.timeName()));

	regAdvKEFile.reset(new OFstream(outFilePath));

	// write header of the log file
	if(!(Pstream::parRun() && !(Pstream::master())))
    {
		regAdvKEFile() << "time" << tab << "regAdvKE(t)" << endl;
		regAdvKEFile().precision(12); // set precision
	}
}
