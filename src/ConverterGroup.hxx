#ifndef _CONVERTERGROUP_HXX	
#define _CONVERTERGROUP_HXX

#include "Converter.hxx"
#include "HtmlConverter.hxx"
#include "PdfConverter.hxx"
#include "Exceptions.hxx"

class ConverterGroup{
	
	protected:
	
	std::list<Converter*> converters;
	
	public:
	
	ConverterGroup(): converters(0){
		
		}
		
	 ~ConverterGroup(){
		 
	while(!converters.empty()) delete converters.front(), converters.pop_front();	
		
		}
	
	void convert(const std::string & name,const std::string & prefix ){
		
		if(converters.empty()){}
				else{
						for( std::list<Converter*>:: iterator it= converters.begin(); it != converters.end(); it++ ){
						(*it)->convert(name,prefix);
	
						}	
				} 	
		}
	

	void add(const std::string type)
	{
	
		if(type =="html"){

			Converter * converter = new HtmlConverter; 
				converters.push_back(converter);
					
		}		
		
		if(type =="pdf_printable"){
			Converter * converter = new PdfConverter; 
				converters.push_back(converter);
					
		}		
		
			
		if(type =="pdf_watermark"){
				Converter * converter = new PdfConverter; 
				converter->activateWatermark("a Watermark");
				converters.push_back(converter);
	
		}		
			if( !(type =="html"  || type =="pdf_printable" || type =="pdf_watermark" ) )
		
				throw UnknownFormat();
	}
	
	
	
	};
#endif
