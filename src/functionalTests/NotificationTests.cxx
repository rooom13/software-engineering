#include "LibFileSystem.hxx"
#include "MailStub.hxx"
#include "MiniCppUnit.hxx"
#include <fstream>
#include "MeltingPotOnline.hxx"


class NotificationTests : public TestFixture<NotificationTests>
{
public:
	TEST_FIXTURE( NotificationTests )
	{
		TEST_CASE( testAssociateTopicWithWork_notifyUsersInDifferentWays );
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
	
	void testAssociateTopicWithWork_notifyUsersInDifferentWays()
	{
		MeltingPotOnline business;
		business.addTopic( "A topic" );
		business.addAuthor( "An author", true );

		business.addClient( "Email client", "email@mail.org" );
		business.addClient( "SMS client", "sms@mail.org" );
		business.clientPrefersSms( "SMS client", "123456789" );
		business.addClient( "Whatsapp client", "whatsapp@mail.org" );
		business.clientPrefersWhatsapp( "Whatsapp client", "987654321" );

		business.subscribeClientToTopic( "Email client", "A topic" );
		business.subscribeClientToTopic( "SMS client", "A topic" );
		business.subscribeClientToTopic( "Whatsapp client", "A topic" );

		createOriginalFile( "original.odt" );
		business.addWork( "An author", "A work", 111, "original.odt" );
		business.associateTopicWithWork( "A topic", "An author", "A work" );

		ASSERT_EQUALS(
			"To: Email client <email@mail.org>\n"
			"Subject: new work A work by An author\n"
			"\n",
			MailStub::theInstance().sentMails()
		)
		ASSERT_EQUALS(
			"SMS to 123456789: [MeltingPot] new work A work by An author\n",
			SmsStub::theInstance().sentMessages()
		)
		ASSERT_EQUALS(
			"Whatsapp to 987654321: [MeltingPot] new work A work by An author\n",
			WhatsappStub::theInstance().sentMessages()
		)
	}
	
};

REGISTER_FIXTURE( NotificationTests )
