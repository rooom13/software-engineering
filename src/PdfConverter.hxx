#ifndef _PDFCONVERTER_HXX_	
#define _PDFCONVERTER_HXX_

#include "libLibreOffice2Pdf.hxx"
#include "Converter.hxx"
#include "Exceptions.hxx"

class PdfConverter :public Converter{
	private:
	std::string watermark; 
	public:
		PdfConverter()
		: Converter(), watermark("")
	{

		}
	~PdfConverter(){}	
	
	void convert(const std::string & name,const std::string &prefix ){
	std::string aux;	
			
		if(watermark == "")
			aux = prefix+" [printable].pdf";
		else 
			aux = prefix+" [watermark].pdf";
	
		try {	
		LibreOfficeTools::convertToPdf(	name,	aux, watermark );
		}
		catch(...){
			
			throw InexistentOrginalFile();
		}
		
		
		}
		
		void  activateWatermark(const std::string wm){
			
				watermark = wm;
				
		}
	
	
	};
	

#endif
