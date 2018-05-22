#ifndef _CHANNEL_HXX
#define _CHANNEL_HXX
#include "MailStub.hxx"
#include "Observer.hxx"
#include "stdlib.h"

//Represents a Novelty
 class Feed{ 
	 
	private:
		std::string _name;
		std::string _title;
	public:
	
		Feed(std::string namein, std::string titlein): 
		_name(namein),_title(titlein){}
		
		/* Returns an item string <item>...<item/> */
		const std::string  item()const
		{
		
		return "<item>\n<title>Novelty: '"+  _title+"' by '"+
		_name+"'</title>\n""<link>http://www.meltingpotonline.com/infoWork?author='"+_name+"'&title='"+_title+"'</link>\n</item>\n""";;
		
		}
};

typedef std::list<Feed*> Feeds;
	
class Channel: public Observer {

private: 

	std::string _name;
	std::string _theme;
	Feeds _newFeeds; 

	
public:


	Channel()
			
		: _name("-- Unnamed --"),
		_theme("-- Unthemed --")
		
	{}
	
	Channel(const std::string & name, const std::string & theme)
			
	{
	_name=name;
	_theme=theme;
	
	}
	
	~Channel(){
		
			while(!_newFeeds.empty()) delete _newFeeds.front(), _newFeeds.pop_front();	
	}

	const std::string & name()const{
		return _name;
	}
	
	
	
	void name( const std::string  & name){
		_name = name;
	}
	
	const std::string & theme()const{
		return _theme;
	}
	
	void theme( const std::string  & theme){
		_theme = theme;
	}
	

	void update(const std::string & t, const std::string &n){
		
		Feed *novedad = new Feed(n,t);

		_newFeeds.push_back(novedad);

		}

		
	const std::string ListNews(){
		

		std::string aux ="";
		for(Feeds::iterator it=_newFeeds.begin(); it !=_newFeeds.end(); it++ ){
		aux += (*it)->item();}
		
		return aux;
		
	}

		
};

#endif
