
#ifndef Controller_hxx
#define Controller_hxx

#include <QObject>
#include <iostream>

#include "LibFileSystem.hxx"
#include "MailStub.hxx"

class Controller : public QObject
{

Q_OBJECT

public:

	Controller()
	{
		LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );
	}

	~Controller()
	{
		LibFileSystem::cleanupDirectory( "config" );
		LibFileSystem::cleanupDirectory( "generated" );
		LibFileSystem::cleanupDirectory( "originals" );
		MailStub::theInstance().removeSent();
	}

public slots:

	void receiveAction( int action, const std::string & author, const std::string & work, const std::string & topic, const std::string & name, int isbn, bool contracted )
	{
		switch( action )
		{
			case 0:
				if ( name == "" ) emit errorMessage( "Enter name" );
				else emit addAuthor( name, contracted );
				break;
			case 1:
				if ( name == "" ) emit errorMessage( "Enter name" );
				else if ( author == "" ) emit errorMessage( "No author selected" );
				else if ( isbn < 0 ) emit errorMessage( "No ISBN selected" );
				else emit addWork( author, name, isbn );
				break;
			case 2:
				if ( name == "" ) emit errorMessage( "Enter name" );
				else emit addTopic( name );
				break;
			case 3:
				if ( topic == "" ) emit errorMessage( "No topic selected" );
				else if ( author == "" ) emit errorMessage( "No author selected" );
				else if ( work == "" ) emit errorMessage( "No work selected" );
				else emit associateTopicWithWork( topic, author, work );
				break;
		}
	}

signals:

	void errorMessage( const QString & error );
	void addAuthor( const std::string & name, bool contracted );
	void addWork( const std::string & authorName, const std::string & name, int isbn );
	void addTopic( const std::string & name );
	void associateTopicWithWork( const std::string & topicName,
	                             const std::string & authorName,
	                             const std::string & workTitle );

};

#endif
