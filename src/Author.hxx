#ifndef _AUTHOR_HXX
#define _AUTHOR_HXX
#include "Work.hxx"
#include "Exceptions.hxx"
#include "Client.hxx"
#include "Subject.hxx"
#include "Channel.hxx"
typedef std::list<Work*> Works;


class Author : public Subject{
	
private: 
	std::string _name;
	bool _isContracted;
	Works _catalogue;


public:
	Author()
			
		: _name("-- Untitled --"),
		_isContracted(false)
	{}
	
	Author(const std::string & name, bool contracted)
			
	{
	
	_name=name;
	_isContracted=contracted;
	
	}
	
	~Author(){ //Destructor, while not empty, delete first of _catalogue and change front pointer
	
		while(!_catalogue.empty()) delete _catalogue.front(), _catalogue.pop_front();
	
	}

	const std::string & name()const{
		return _name;
	}
	
	void name( const std::string  & name){
		_name = name;
	}
	
	const bool  isContracted() const{
		return _isContracted;	
	}	


	void contract () {
		_isContracted = true;	
	}
	
	void fire () {
		_isContracted = false;	
	}
	
	const std::string  catalogue(){
		
		std::string worksC;
	
		for(Works::iterator it= _catalogue.begin(); it != _catalogue.end(); it++ ){
			
			worksC += "\t" + (*it)->aText()+"\n";
		}


		return worksC;
	}
	
	void addWork(const std::string & title, const int & id,const std::string  & file ){
		
		Work *work = new Work(title,id,file);
	
		_catalogue.push_back(work);
		
		notify( work->title(), name() );

	}


	
	Work & findWork(const std::string & title){
	 const std::string a=title;
		for(Works::iterator it= _catalogue.begin(); it != _catalogue.end(); it++ ){
			if( (*it)->title().compare(title) == 0 ){
				/* Doble ** porque tenemos 
				que retornar una instancia, 
				pero por referencia*/
				return *(*it);
				}
		}
		
		throw InexistentWork();
	} 
	
	const std::string description()const{
		
		std::string aux;
	
		for(Works::const_iterator it= _catalogue.begin(); it != _catalogue.end(); it++ ){
			aux+="\t"+(*it)->aText()+"\n";
			}
		
		if (_isContracted==false)
	
		return _name + " [external]\n" +aux;
	
		else return _name + " [contracted]\n" +aux;
		
	}
		
		
		void notify(const std::string t, const std::string n){
		
		Subject::notify(t, n);
	
		}

};

#endif
