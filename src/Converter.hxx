#ifndef _CONVERTER_HXX	
#define _CONVERTER_HXX
#include "Exceptions.hxx"


class Converter{
	
	public:
	
	Converter(){}
		
	virtual ~Converter(){}
	
	virtual void  convert(const std::string & name,const std::string & prefix ){};
	
	virtual void  activateWatermark(const std::string wm){};
	};
#endif
