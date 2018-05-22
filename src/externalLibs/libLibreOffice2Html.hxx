#ifndef libLibreOffice2Html
#define libLibreOffice2Html

#include <fstream>

/**
 * Simulates the conversion of an Odt file into a War file.
 * a War file is just a compressed directory with html files and images.
 * In reality it simply writes a string describing the process.
 *  - returns -1 if input file doesn't exist
 *  - returns 0 if conversion is ok
 **/
inline int OO_WarGeneration( const char* inOdtFile, const char* outWarFile )
{
	std::ifstream odt;
	odt.open( inOdtFile );
	if ( !odt.is_open() ) return -1;

	std::ofstream warfile( outWarFile );
	if ( !warfile.is_open() ) return -2;
	warfile << "War file generated from '" << inOdtFile << "'" << std::endl;
	return 0;
}

#endif

