#include "MiniCppUnit.hxx"
#include "Author.hxx"
#include "Collection.hxx"

class AddAuthorAndWorkTests : public TestFixture<AddAuthorAndWorkTests>
{
public:
	TEST_FIXTURE( AddAuthorAndWorkTests )
	{
		TEST_CASE( testCatalogue_withoutWorks );
		TEST_CASE( testCatalogue_withOneWork );
		TEST_CASE( testCatalogue_withTwoWorks );
		TEST_CASE( testFindWork_withTwoWorks );
		TEST_CASE( testFindWork_withInexistentWork );
		TEST_CASE( testDescription_withoutWorks );
		TEST_CASE( testDescription_withWorks );
		TEST_CASE( testWorkList_withoutWorks );
		TEST_CASE( testWorkList_withOneWork );
		TEST_CASE( testWorkList_withTwoWorks );
	}
	void testCatalogue_withoutWorks()
	{
		Author author;
		
		ASSERT_EQUALS(
			"",
			author.catalogue()
		)
	}
	void testCatalogue_withOneWork()
	{
		Author author;
		author.addWork( "A work", 123, "aFile.odt" );
		
		ASSERT_EQUALS(
			"\t123, 'A work', 'originals/aFile.odt'\n",
			author.catalogue()
		)
	}
	void testCatalogue_withTwoWorks()
	{
		Author author;
		author.addWork( "A work", 111, "aFile.odt" );
		author.addWork( "Another work", 222, "anotherFile.odt" );
		
		ASSERT_EQUALS(
			"\t111, 'A work', 'originals/aFile.odt'\n"
			"\t222, 'Another work', 'originals/anotherFile.odt'\n",
			author.catalogue()
		)
	}
	void testFindWork_withTwoWorks()
	{
		Author author;
		author.addWork( "A work", 111, "aFile.odt" );
		author.addWork( "Another work", 222, "anotherFile.odt" );

		Work & work = author.findWork( "A work" );

		ASSERT_EQUALS(
			"A work",
			work.title()
		)
	}
	void testFindWork_withInexistentWork()
	{
		Author author;

		try
		{
			author.findWork( "A work" );
			FAIL( "An exception should be caught!" );		
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The work does not exist",
				e.what()
			)
		}
	}
	void testDescription_withoutWorks()
	{
		Author author;
		author.name( "An author" );
		
		ASSERT_EQUALS(
			"An author [external]\n",
			author.description()
		)
	}
	void testDescription_withWorks()
	{
		Author author;
		author.name( "An author" );
		author.contract();

		author.addWork( "A work", 111, "aFile.odt" );
		author.addWork( "Another work", 222, "anotherFile.odt" );
		
		ASSERT_EQUALS(
			"An author [contracted]\n"
			"\t111, 'A work', 'originals/aFile.odt'\n"
			"\t222, 'Another work', 'originals/anotherFile.odt'\n",
			author.description()
		)
	}
	void testWorkList_withoutWorks()
	{
		Collection collection;
		
		ASSERT_EQUALS(
			"",
			collection.workList()
		)
	}
	void testWorkList_withOneWork()
	{
		Author author;
		author.addWork( "A work", 111, "aFile.odt" );
		author.addWork( "Another work", 222, "anotherFile.odt" );

		Collection collection;
		Work & work = author.findWork( "A work" );
		collection.addWork( work );
		
		ASSERT_EQUALS(
			"1: 111, 'A work', 'originals/aFile.odt'\n",
			collection.workList()
		)
	}
	void testWorkList_withTwoWorks()
	{
		Author author;
		author.addWork( "A work", 111, "aFile.odt" );
		author.addWork( "Another work", 222, "anotherFile.odt" );

		Collection collection;
		Work & work1 = author.findWork( "A work" );
		collection.addWork( work1 );
		Work & work2 = author.findWork( "Another work" );
		collection.addWork( work2 );
		
		ASSERT_EQUALS(
			"1: 111, 'A work', 'originals/aFile.odt'\n"
			"2: 222, 'Another work', 'originals/anotherFile.odt'\n",
			collection.workList()
		)
	}

};

REGISTER_FIXTURE( AddAuthorAndWorkTests )

