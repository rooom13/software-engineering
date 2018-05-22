
#ifndef _HTMLCONVERTER_HXX	
#define _HTMLCONVERTER_HXX
#include "Exceptions.hxx"
#include "Converter.hxx"
class HtmlConverter :public Converter{
	
	public:
	HtmlConverter()
	: Converter()
	{}
	~HtmlConverter(){}
	
	void convert(const std::string & name,const std::string & prefix ){
			std::string aux=name;

			std::ifstream originalFile (aux.c_str());
			
			if (originalFile == 0){ 
				
				throw InexistentOrginalFile();
			
			}
			
			else {
				
			aux=prefix+" [multiple HTML files].war";
		
			std::ofstream newfile(aux.c_str());
			
		}
	
		}
	
	};
#endif
