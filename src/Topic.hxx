#ifndef _TOPIC_HXX_
#define _TOPIC_HXX_
#include "Client.hxx"
#include <fstream>
#include <stdlib.h>
#include "Subject.hxx"


class Topic : public Subject {
private: 
	std::string _name;

public:

	Topic()
	: _name("-- Default --")
	{}
	
	
	Topic( const std::string & name)
	: _name(name)
	{}
	
	~Topic()
	{
			
		} 
	
	const std::string & name()const{
		return _name;
	}

	void name( const std::string  & name){
		_name = name;
	}
	
	void addClient(Client & client ){
		
	
		addObserver(&client);
		
		}
		
		
	const std::string listClients()
		{
	
			return Subject::listObservers();
		
		}
		
	void notify(const std::string aux, const std::string aux2){
		
		Subject::notify(aux,aux2);
		
		}
};
#endif
