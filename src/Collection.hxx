#ifndef _COLLECTION_HXX
#define _COLLECTION_HXX
#include "Work.hxx"
#include <string.h>
#include <stdio.h>
#include "Subject.hxx"

typedef std::list<Work*> Works;
class Collection : public Subject {
private: 
	std::string _title;
	bool _isPublished;
	Works _worklist;

public:
	Collection()
			
		: _title("-- Untitled --"),
		_isPublished(false)
	{
	}

	~Collection()
	{
			
	}
	
	const std::string & title()const{
		return _title;
	}

	void title( const std::string  & title){
		_title = title;
	}

	const bool  isPublished() const{
		return _isPublished;	
	}	
	
	void publish () {
		_isPublished = true;	
	}

	void withdraw () {
		_isPublished = false;	
	}
	
	const std::string workList () const{
		
		 std::string aux = "";
		 std::stringstream numerito;
		
		 
		if (_worklist.empty()) return aux;
		
		else {
		int count = 1;
		for(Works::const_iterator it= _worklist.begin(); it != _worklist.end(); it++, count++ ){
			numerito<<count;
				
			aux += numerito.str() + ": "+(*it)->aText()+"\n";
			numerito.str("");
			}
			
		}
		return aux;
	}
	
	void addWork( Work & work ){
		
		_worklist.push_back(&work);

	}
		
	
};

#endif
