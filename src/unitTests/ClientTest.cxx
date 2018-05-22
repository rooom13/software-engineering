#include "MailStub.hxx"
#include "MiniCppUnit.hxx"
#include "LibFileSystem.hxx"
#include "Client.hxx"

class  ClientTests : public TestFixture< ClientTests >
{
public:
	TEST_FIXTURE( ClientTests )
	{
     	TEST_CASE( testName_byDefault );
		TEST_CASE( testName_addingName );
		TEST_CASE( testMail_byDefault );
		 TEST_CASE( testMail_addingMail );
		 TEST_CASE ( testClient_update );
	
	}
	
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "config" );
		LibFileSystem::cleanupDirectory( "generated" );
		LibFileSystem::cleanupDirectory( "originals" );
		MailStub::theInstance().removeSent();
	}
	
	void testName_byDefault()
	{
		Client client;
		
		ASSERT_EQUALS( "-- Untitled --", client.name() );
	}

	void testName_addingName()
	{
		Client client;
		client.name( "Roman dios" );
		ASSERT_EQUALS( "Roman dios", client.name() );
	}
	
	void testMail_byDefault()
	{
		Client client;
		
		ASSERT_EQUALS( "-- unmailed --", client.mail() );
	}

	void testMail_addingMail()
	{
		Client client;
		client.mail( "Roman dios" );
		ASSERT_EQUALS( "Roman dios", client.mail() );
	}
	void testClient_update()
	{	
		//MailStub::theInstance().removeSent(); //good
		Client client;
		client.name("A client"); 
		client.mail("a@mail.org");
		
		client.update("A work","An author");
		
		ASSERT_EQUALS( "To: A client <a@mail.org>\n"
		"Subject: new work A work by An author\n\n", MailStub::theInstance().sentMails());
		
		
		
	}
};

REGISTER_FIXTURE( ClientTests )

