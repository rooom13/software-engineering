#include "MiniCppUnit.hxx"
#include "Channel.hxx"

class  ChannelTests : public TestFixture< ChannelTests >
{
public:
	TEST_FIXTURE( ChannelTests )
	{
     		TEST_CASE( testName_byDefault );
		TEST_CASE( testName_addingName );
		TEST_CASE( testTheme_byDefault );
		TEST_CASE( testTheme_addingTheme );
		
		TEST_CASE( testListFeed_withoutFeed );
		TEST_CASE( testListFeed_withFeed );
		TEST_CASE( testListFeed_withMoreThanONeFeed );
	}
	
	
	
	
	void testName_byDefault()
	{
		Channel channel;
		
		ASSERT_EQUALS( "-- Unnamed --", channel.name() );
	}

	void testName_addingName()
	{
		Channel channel;
		channel.name( "aChannel" );
		ASSERT_EQUALS( "aChannel", channel.name() );
	}
	
	void testTheme_byDefault()
	{
		Channel channel;
		
		ASSERT_EQUALS( "-- Unthemed --", channel.theme() );
	}

	void testTheme_addingTheme()
	{
		Channel channel;
		channel.theme( "Psytrance" );
		ASSERT_EQUALS( "Psytrance", channel.theme() );
	}
	
	void testListFeed_withoutFeed()
	{
		Channel channel;
		
	
		
		ASSERT_EQUALS( "", channel.ListNews() );
		
	}
	
	void testListFeed_withFeed()
	{
		Channel channel;
		channel.update("The Hobbit","Tolkien");
	
		
		ASSERT_EQUALS( 
			"<item>\n"
			"<title>Novelty: 'The Hobbit' by 'Tolkien'</title>\n"
			"<link>http://www.meltingpotonline.com/infoWork?author='Tolkien'&title='The Hobbit'</link>\n"
			"</item>\n""", channel.ListNews() );
		
	}
	void testListFeed_withMoreThanONeFeed()
	{
		Channel channel;
		channel.update( "Best rapper","Anders");
		channel.update( "Best person","Kalpani");
		channel.update("Best dancer","Pritish" );
		channel.update("Best body builder","Javi" );
		ASSERT_EQUALS( 
			"<item>\n"
			"<title>Novelty: 'Best rapper' by 'Anders'</title>\n"
			"<link>http://www.meltingpotonline.com/infoWork?author='Anders'&title='Best rapper'</link>\n"
			"</item>\n"
			"<item>\n"
			"<title>Novelty: 'Best person' by 'Kalpani'</title>\n"
			"<link>http://www.meltingpotonline.com/infoWork?author='Kalpani'&title='Best person'</link>\n"
			"</item>\n"
			"<item>\n"
			"<title>Novelty: 'Best dancer' by 'Pritish'</title>\n"
			"<link>http://www.meltingpotonline.com/infoWork?author='Pritish'&title='Best dancer'</link>\n"
			"</item>\n"
			"<item>\n"
			"<title>Novelty: 'Best body builder' by 'Javi'</title>\n"
			"<link>http://www.meltingpotonline.com/infoWork?author='Javi'&title='Best body builder'</link>\n"
			"</item>\n"
			
			, channel.ListNews() );
		
	}
	
		
};

REGISTER_FIXTURE( ChannelTests )

