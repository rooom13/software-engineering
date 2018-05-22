#include "MiniCppUnit.hxx"
#include "Topic.hxx"

class  TopicTests : public TestFixture< TopicTests >
{
public:
	TEST_FIXTURE( TopicTests )
	{
     	TEST_CASE( testName_byDefault );
		TEST_CASE( testName_addingName );
		TEST_CASE( testListClients_withoutClients );
		TEST_CASE( testListClients_withClients );
		TEST_CASE( testTopic_notify ); 
	
	}
	
	
	
	
	void testName_byDefault()
	{
		Topic topic;
		
		ASSERT_EQUALS( "-- Default --", topic.name() );
	}

	void testName_addingName()
	{
		Topic topic;
		topic.name( "Xiwei" );
		ASSERT_EQUALS( "Xiwei", topic.name() );
	}
	
	void testListClients_withoutClients()
	{
		Topic topic;
		Client client;
	
		
		ASSERT_EQUALS( "", topic.listClients() );
		
	}
	void testListClients_withClients()
	{
		Topic topic;
		Client client1,client2;
		client1.name("Jose");
		client2.name("JosePedro");
		topic.addClient(client1);
		topic.addClient(client2);

		
		ASSERT_EQUALS( "Jose\nJosePedro\n", topic.listClients() );
		
	}
	
	   void testTopic_notify()
    {
    //TO clean mail added in tearDown
    	//MailStub::theInstance().removeSent();
        Topic topic;
        topic.name( "a Topic");

        Client clienta;
        Client clientb;
       
        clienta.name("Client a");
        clienta.mail("emaila@gmail.com");
        clientb.name("Client b");
        clientb.mail("anotherMail@gmail.com");

        topic.addClient(clienta);
        topic.addClient(clientb);

        
        topic.notify("A work", "An author");

        ASSERT_EQUALS(
            "To: Client a <emaila@gmail.com>\n"
            "Subject: new work A work by An author\n"
            "\n"
            "To: Client b <anotherMail@gmail.com>\n"
            "Subject: new work A work by An author\n"
            "\n",
            MailStub::theInstance().sentMails()
        );
       tearDown();
    }
	
		
};

REGISTER_FIXTURE( TopicTests )

