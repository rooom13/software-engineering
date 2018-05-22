#include "MiniCppUnit.hxx"
#include "Collection.hxx"

class CollectionTests : public TestFixture<CollectionTests>
{
public:
	TEST_FIXTURE( CollectionTests )
	{
		TEST_CASE( testTitle_byDefault );
		TEST_CASE( testTitle_addingTitle );
		TEST_CASE( testPublished_byDefault );
		TEST_CASE( testPublished_afterPublishing );
		TEST_CASE( testPublished_afterWithdrawing );
	}
	void testTitle_byDefault()
	{
		Collection collection;
		ASSERT_EQUALS( "-- Untitled --", collection.title() );
	}
	void testTitle_addingTitle()
	{
		Collection collection;
		collection.title( "A Title" );
		ASSERT_EQUALS( "A Title", collection.title() );
	}
	void testPublished_byDefault()
	{
		Collection collection;
		ASSERT_EQUALS( false, collection.isPublished() );
	}
	void testPublished_afterPublishing()
	{
		Collection collection;
		collection.publish();
		ASSERT_EQUALS( true, collection.isPublished() );
	}
	void testPublished_afterWithdrawing()
	{
		Collection collection;
		collection.publish();
		collection.withdraw();
		ASSERT_EQUALS( false, collection.isPublished() );
	}
};

REGISTER_FIXTURE( CollectionTests )

