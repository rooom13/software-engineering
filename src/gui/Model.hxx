
#ifndef Model_hxx
#define Model_hxx

#include <QObject>
#include <fstream>
#include <iostream>

#include "LibFileSystem.hxx"

class Model : public QObject
{

Q_OBJECT

public:

	virtual ~Model() {}
	virtual  std::string catalogue() const = 0;
	virtual std::string listTopics() const = 0;
	virtual void addAuthor( const std::string & name, bool contracted ) = 0;
	virtual void addWork( const std::string & authorName, const std::string & title, int isbn, const std::string & original ) = 0;
	virtual void addTopic( const std::string & name ) = 0;
	virtual void associateTopicWithWork( const std::string & topicName,
	                                     const std::string & authorName,
	                                     const std::string & workTitle ) = 0;

public slots:

	void doAddAuthor( const std::string & name, bool group )
	{
		addAuthor( name, group );
		emit modify( catalogue(), listTopics() );
	}
	
	void doAddWork( const std::string & authorName, const std::string & title, int isbn )
	{
		std::string fullname( "originals/" );
		fullname += title;
		std::ofstream os( fullname.c_str() );
		os << "An original file" << std::endl;
		os.close();

		LibFileSystem::listDirectoryInOrder( "originals" );

		addWork( authorName, title, isbn, title );
		emit modify( catalogue(), listTopics() );
	}

	void doAddTopic( const std::string & topicName )
	{
		addTopic( topicName );
		emit modify( catalogue(), listTopics() );
	}

	void doAssociateTopicWithWork( const std::string & topicName,
	                               const std::string & authorName,
	                               const std::string & workTitle )
	{
		associateTopicWithWork( topicName, authorName, workTitle );
		emit modify( catalogue(), listTopics() );
	}

signals:

	void modify( const std::string & catalogue, const std::string & topicList );

};

#endif
