#include "LibFileSystem.hxx"
#include "MailStub.hxx"
#include "MiniCppUnit.hxx"
#include <fstream>
#include "MeltingPotOnline.hxx"


class SubscriptionTests : public TestFixture<SubscriptionTests>
{
public:
	TEST_FIXTURE( SubscriptionTests )
	{
		TEST_CASE( testListTopics_withOneTopic );
		TEST_CASE( testListTopics_withTwoTopics );
		TEST_CASE( testAssociateTopicWithWork_withInexistentTopic );
		TEST_CASE( testAssociateTopicWithWork_workWithTwoTopics );
		TEST_CASE( testListClients_withOneClient );
		TEST_CASE( testListClients_withTwoClients );
		TEST_CASE( testListSubscribedToTopic_withOneUser );
		TEST_CASE( testListSubscribedToTopic_withTwoUsers );
		TEST_CASE( testListSubscribedToTopic_withInexistentClient );
		TEST_CASE( testListSubscribedToTopic_withInexistentTopic );
		TEST_CASE( testAssociateTopicWithWork_notifySubscribedClient );
		TEST_CASE( testAssociateTopicWithWork_notifyTwoClientsSubscribedToTwoTopics );
	}

	/**
	 * setUp is automatically called before each test case
	 */
	void setUp()
	{
		LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );
	}

	/**
	 * tearDown is automatically called after each test case
	 */
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "config" );
		LibFileSystem::cleanupDirectory( "generated" );
		LibFileSystem::cleanupDirectory( "originals" );
		MailStub::theInstance().removeSent();
	}

	void createOriginalFile( const std::string & name )
	{
		std::string fullname( "originals/" );
		fullname += name;
		std::ofstream os( fullname.c_str() );
		os << "An original file" << std::endl;
		os.close();
	}

	
	void testListTopics_withOneTopic()
	{
		MeltingPotOnline business;
		business.addTopic( "Computer Science" );
		ASSERT_EQUALS(
			"Computer Science\n", 
			business.listTopics()
		);
	}
	
	void testListTopics_withTwoTopics()
	{
		MeltingPotOnline business;
		business.addTopic( "Literature" );
		business.addTopic( "Economics" );
		ASSERT_EQUALS(
			"Literature\n"
			"Economics\n", 
			business.listTopics()
		);
	}
	
	void testAssociateTopicWithWork_withInexistentTopic()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );
		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 123, "aFile.odt" );
		try
		{
			business.associateTopicWithWork( "Inexistent topic", "An author", "A work" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The topic does not exist",
				e.what()
			)
		}
	}

	
	void testAssociateTopicWithWork_workWithTwoTopics()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );
		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 123, "aFile.odt" );

		business.addTopic( "Topic 1" );
		business.addTopic( "Topic 2" );
		business.associateTopicWithWork( "Topic 1", "An author", "A work" );
		business.associateTopicWithWork( "Topic 2", "An author", "A work" );
		ASSERT_EQUALS(
			"An author [external]\n"
			"\t123, 'A work', 'originals/aFile.odt'\n"
			"\t\t'Topic 1'\n"
			"\t\t'Topic 2'\n",
			business.catalogue()
		);
	}
	
	
	void testListClients_withOneClient()
	{
		MeltingPotOnline business;
		business.addClient( "A client", "a@mail.org" );
		ASSERT_EQUALS(
			"A client <a@mail.org>\n",
			business.listClients()
		);
	}
	
	void testListClients_withTwoClients()
	{
		MeltingPotOnline business;
		business.addClient( "A client", "a@mail.org" );
		business.addClient( "Another client", "another@mail.org" );
		ASSERT_EQUALS(
			"A client <a@mail.org>\n"
			"Another client <another@mail.org>\n",
			business.listClients()
		);
	}
	
	void testListSubscribedToTopic_withOneUser()
	{
		MeltingPotOnline business;
		business.addClient( "A client", "a@mail.org" );
		business.addTopic( "A topic" );
		business.subscribeClientToTopic( "A client", "A topic" );
		ASSERT_EQUALS(
			"A client\n",
			business.listSubscribedToTopic( "A topic" )
		);
	}
	
	void testListSubscribedToTopic_withTwoUsers()
	{
		MeltingPotOnline business;
		business.addClient( "A client", "a@mail.org" );
		business.addClient( "Another client", "another@mail.org" );
		business.addTopic( "A topic" );
		business.subscribeClientToTopic( "A client", "A topic" );
		business.subscribeClientToTopic( "Another client", "A topic" );
		ASSERT_EQUALS(
			"A client\n"
			"Another client\n",
			business.listSubscribedToTopic( "A topic" )
		);
	}
	
	void testListSubscribedToTopic_withInexistentClient()
	{
		MeltingPotOnline business;
		business.addTopic( "A topic" );
		try
		{
			business.subscribeClientToTopic( "Inexistent client", "A topic" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The client does not exist",
				e.what()
			)
		}
	}
	
	void testListSubscribedToTopic_withInexistentTopic()
	{
		MeltingPotOnline business;
		business.addClient( "A client", "a@mail.org" );
		try
		{
			business.subscribeClientToTopic( "A client", "Inexistent topic" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The topic does not exist",
				e.what()
			)
		}

	}
	
	void testAssociateTopicWithWork_notifySubscribedClient()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );

		business.addTopic( "A topic" );
		business.addClient( "A client", "a@mail.org" );
		business.subscribeClientToTopic( "A client", "A topic" );

		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 123, "aFile.odt" );
		business.associateTopicWithWork( "A topic", "An author", "A work" );

		ASSERT_EQUALS(
			"To: A client <a@mail.org>\n"
			"Subject: new work A work by An author\n"
			"\n",
			MailStub::theInstance().sentMails()
		);
	}
	
	void testAssociateTopicWithWork_notifyTwoClientsSubscribedToTwoTopics()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );

		business.addTopic( "Topic 1" );
		business.addTopic( "Topic 2" );
		business.addClient( "One client", "one@mail.org" );
		business.addClient( "Another client", "another@mail.org" );

		business.subscribeClientToTopic( "One client", "Topic 1" );
		business.subscribeClientToTopic( "Another client", "Topic 2" );

		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 123, "aFile.odt" );
		business.associateTopicWithWork( "Topic 1", "An author", "A work" );
		business.associateTopicWithWork( "Topic 2", "An author", "A work" );

		// Note that messages are listed in alphabetic order!
		ASSERT_EQUALS(
			"To: Another client <another@mail.org>\n"
			"Subject: new work A work by An author\n"
			"\n"
			"To: One client <one@mail.org>\n"
			"Subject: new work A work by An author\n"
			"\n",
			MailStub::theInstance().sentMails()
		);
	}
	
};

REGISTER_FIXTURE( SubscriptionTests )


