#ifndef _libLibreOffice_hxx_
#define _libLibreOffice_hxx_

#include <string>
#include <fstream>

namespace LibreOfficeTools
{

	class LOWriterFileNotFound {}; //< An empty exception class.

	/*
	 * Simulates the generation of a PDF file from an OOWriter file (odt)
	 * In reality it simply writes a string describing the process.
	 * throws OOWriterFileNotFound when the inOOWriterFile doesn't exist.
	 * Parameter watermarkString is the text that will fill the background
	 * canvas.
	 */
	inline void convertToPdf( 
			const std::string& inLOWriterFile, 
			const std::string& outFilename,
			const std::string& watermarkString = "" )
	{
		std::ifstream odt;
		odt.open( inLOWriterFile.c_str() );
		if ( !odt.is_open() ) throw LOWriterFileNotFound(); 

		std::ofstream pdfFile( outFilename.c_str() );
		pdfFile << "PDF generated from '" << inLOWriterFile 
			<<"'. Watermark: '"<< watermarkString << "'" << std::endl;
	}

} // namespace

#endif
