#include "LibFileSystem.hxx"
#include "MailStub.hxx"
#include "MiniCppUnit.hxx"
#include <fstream>
#include "MeltingPotOnline.hxx"

class AdvancedSubscriptionTests : public TestFixture<AdvancedSubscriptionTests>
{
public:
	TEST_FIXTURE( AdvancedSubscriptionTests )
	{
		TEST_CASE( testAddWork_notifyClientSubscribedToAuthor );
		TEST_CASE( testAddWork_notifyTwoClientsSubscribedToTwoAuthors );
		TEST_CASE( testListThematicChannels );
		TEST_CASE( testRssByChannel_withoutNotification );
		TEST_CASE( testRssByChannel_withInexistentChannel );
		TEST_CASE( testRssByChannel_withNotifiedWork );
		TEST_CASE( testRssByChannel_subscribedToAuthorAndTopic );
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
	
	void testAddWork_notifyClientSubscribedToAuthor()
	{
		MeltingPotOnline business;
		business.addAuthor( "Saramago", false );
		business.addClient( "A client", "a@mail.org" );
		business.subscribeClientToAuthor( "A client", "Saramago" );

		createOriginalFile( "ceguera.odt" );
		business.addWork( "Saramago", "Ensayo sobre la ceguera", 22, "ceguera.odt" );

		ASSERT_EQUALS(
			"To: A client <a@mail.org>\n"
			"Subject: new work Ensayo sobre la ceguera by Saramago\n"
			"\n",
			MailStub::theInstance().sentMails()
		);
	}
	
	void testAddWork_notifyTwoClientsSubscribedToTwoAuthors()
	{
		MeltingPotOnline business;
		business.addAuthor( "Saramago", false );
		business.addAuthor( "Tolkien", false );
		business.addClient( "A client", "a@mail.org" );
		business.addClient( "Another client", "another@mail.org" );

		business.subscribeClientToAuthor( "A client", "Saramago" );
		business.subscribeClientToAuthor( "Another client", "Tolkien" );

		createOriginalFile( "ceguera.odt" );
		business.addWork( "Saramago", "Ensayo sobre la ceguera", 111, "ceguera.odt" );
		createOriginalFile( "hobbit.odt" );
		business.addWork( "Tolkien", "The Hobbit", 222, "hobbit.odt" );

		ASSERT_EQUALS(
			"To: A client <a@mail.org>\n"
			"Subject: new work Ensayo sobre la ceguera by Saramago\n"
			"\n"
			"To: Another client <another@mail.org>\n"
			"Subject: new work The Hobbit by Tolkien\n"
			"\n",
			MailStub::theInstance().sentMails()
		)
	}
	
	void testListThematicChannels()
	{
		MeltingPotOnline business;
		business.addChannel( "Rivendel", "Rivendel: The MeltingPot fantasy channel" );
		business.addChannel( "Business", "Economy for the professional" );

		ASSERT_EQUALS(
			"Rivendel\n"
			"\tRivendel: The MeltingPot fantasy channel\n"
			"Business\n"
			"\tEconomy for the professional\n",
			business.listThematicChannels()
		)
	}
	
	void testRssByChannel_withoutNotification()
	{
		MeltingPotOnline business;
		business.addAuthor( "Tolkien", false );
		business.addChannel( "Rivendel", "Rivendel: The MeltingPot fantasy channel" );
		
		ASSERT_EQUALS(
			"<?xml version='1.0' encoding='UTF-8' ?>\n"
			"<rss version='2.0'>\n"
			"<channel>\n"
			"<title>MeltingPotOnline: Rivendel</title>\n"
			"<link>http://www.meltingpotonline.com/Rivendel</link>\n"
			"<description>Rivendel: The MeltingPot fantasy channel</description>\n"
			"</channel>\n"
			"</rss>\n",
			business.rssByChannel( "Rivendel" )
		)
	}
	
	void testRssByChannel_withInexistentChannel()
	{
		MeltingPotOnline business;
		business.addChannel( "Rivendel", "Rivendel: The MeltingPot fantasy channel" );

		try
		{
			business.rssByChannel( "InexistentChannel" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The thematic channel does not exist",
				e.what()
			)
		}
	}
	void testRssByChannel_withNotifiedWork()
	{
		MeltingPotOnline business;
		business.addAuthor( "Tolkien", false );
		business.addChannel( "Rivendel", "Rivendel: The MeltingPot fantasy channel" );

		business.subscribeChannelToAuthor( "Rivendel", "Tolkien" );
	
		createOriginalFile( "hobbit.odt" );
		business.addWork( "Tolkien", "The Hobbit", 11, "hobbit.odt" );
		//SI DESCOMENTAS ESTO VA
		//Channel & channel = business.findChannel("Rivendel");
		//channel.update("The Hobbit","Tolkien");		
			
		ASSERT_EQUALS(
			"<?xml version='1.0' encoding='UTF-8' ?>\n"
			"<rss version='2.0'>\n"
			"<channel>\n"
			"<title>MeltingPotOnline: Rivendel</title>\n"
			"<link>http://www.meltingpotonline.com/Rivendel</link>\n"
			"<description>Rivendel: The MeltingPot fantasy channel</description>\n"
			"<item>\n"
			"<title>Novelty: 'The Hobbit' by 'Tolkien'</title>\n"
			"<link>http://www.meltingpotonline.com/infoWork?author='Tolkien'&title='The Hobbit'</link>\n"
			"</item>\n"
			"</channel>\n"
			"</rss>\n",
			business.rssByChannel( "Rivendel" )
		)
	}
	void testRssByChannel_subscribedToAuthorAndTopic()
	{
		MeltingPotOnline business;
		business.addChannel( "Business", "Economy for the professional" );

		business.addTopic( "Economy" );
		business.addAuthor( "Adam Smith", true );
		business.addAuthor( "Mario Conde", true );

		business.subscribeChannelToAuthor( "Business", "Adam Smith" );
		business.subscribeChannelToTopic( "Business", "Economy" );

		createOriginalFile( "nations.odt" );
		business.addWork( "Adam Smith", "The Wealth of Nations", 1, "nations.odt" );
		createOriginalFile( "stealing.odt" );
		business.addWork( "Mario Conde", "The Art of Stealing", 2, "stealing.odt" );
		business.associateTopicWithWork( "Economy", "Mario Conde", "The Art of Stealing" );

		ASSERT_EQUALS(
			"<?xml version='1.0' encoding='UTF-8' ?>\n"
			"<rss version='2.0'>\n"
			"<channel>\n"
			"<title>MeltingPotOnline: Business</title>\n"
			"<link>http://www.meltingpotonline.com/Business</link>\n"
			"<description>Economy for the professional</description>\n"
			"<item>\n"
			"<title>Novelty: 'The Wealth of Nations' by 'Adam Smith'</title>\n"
			"<link>http://www.meltingpotonline.com/infoWork?author='Adam Smith'&title='The Wealth of Nations'</link>\n"
			"</item>\n"
			"<item>\n"
			"<title>Novelty: 'The Art of Stealing' by 'Mario Conde'</title>\n"
			"<link>http://www.meltingpotonline.com/infoWork?author='Mario Conde'&title='The Art of Stealing'</link>\n"
			"</item>\n"
			"</channel>\n"
			"</rss>\n",
			business.rssByChannel( "Business" )
		)
	}
	
};

REGISTER_FIXTURE( AdvancedSubscriptionTests )

