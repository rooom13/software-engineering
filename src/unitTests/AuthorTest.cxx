#include "MiniCppUnit.hxx"
#include "Author.hxx"

class  AuthorTests : public TestFixture< AuthorTests >
{
public:
	TEST_FIXTURE( AuthorTests )
	{
     		TEST_CASE( testName_byDefault );
		TEST_CASE( testName_addingName );
		TEST_CASE( testContract_byDefault );
		TEST_CASE( testContract_afterContracting );
		TEST_CASE( testContract_fired );
	}
	
	void testName_byDefault()
	{
		Author author;
		
		ASSERT_EQUALS( "-- Untitled --", author.name() );
	}

	void testName_addingName()
	{
		Author author;
		author.name( "Roman dios" );
		ASSERT_EQUALS( "Roman dios", author.name() );
	}
	
	void testContract_byDefault()
	{
		Author author;
		
		ASSERT_EQUALS( false, author.isContracted() );
		
	}
	
	void testContract_afterContracting()
	{
		Author author;
		author.contract();
		ASSERT_EQUALS( true, author.isContracted() );
	}
	
	void testContract_fired()
	{
		Author author;
		author.fire();
		ASSERT_EQUALS( false, author.isContracted() );
	}
};

REGISTER_FIXTURE( AuthorTests )

