#ifndef _WORK_HXX
#define _WORK_HXX
#include <stdlib.h>
#include "Topic.hxx"

typedef std::list<Topic*> Topics;

class Work
{
private: 
	std::string _title;
	int _isbn;
	std::string _originalFile;
	Topics _topics;
public:
	Work()
	 	
		: _title("-- Untitled --"),_isbn(-1),
		_originalFile("")
	{		
	}

	Work( const std::string & title, const int & isbn, const std::string & original)
	: _title(title),_isbn(isbn),
		_originalFile(original)
	
	{
		
	}
	
	~Work()
	{
			while(!_topics.empty()) delete _topics.front(), _topics.pop_front();	
	}
	

	const std::string & title()const{
		return _title;
	}

	void title( const std::string  & title){
		_title = title;
	}

	const int & isbn() const{
		return _isbn;	
	}	
	
	void isbn(const int & isbn) {
		_isbn = isbn;	
	}

	const std::string & originalFile()const{
		return _originalFile;
	}
	
	void originalFile(const std::string & originalFile) {
		_originalFile = originalFile;	
	}

	const std::string  aText(){
		std::string dir;
		dir = "";	
		std::string topic = listTopics();
		std::stringstream linia;
		
		if( !_originalFile.empty() ) dir = "originals/";		
		
		linia <<_isbn<< ", '" <<_title<<"', '"<<dir<<_originalFile<<"'"<<topic;
		
		dir = linia.str();
		
	return dir;
	
	}

	void addTopic(const std::string & name){
				
		Topic *topic= new Topic(name);
		_topics.push_back(topic);
				
	}
				
			
	const std::string listTopics(){
		
		std::string topicsList;
		for(Topics::iterator it=_topics.begin(); it !=_topics.end(); it++ ){
			topicsList += "\n\t\t'"+(*it)->name() +"'";

		}
		
		return topicsList;
		}
};
#endif

/*

git add unitTests/WorkTests.cxx 

git add Work.hxx

git commit -m "GREEN: ItemTests::testTitle_addingTitle"

*/
