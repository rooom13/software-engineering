#include "LibFileSystem.hxx"
#include "MiniCppUnit.hxx"
#include "MeltingPotOnline.hxx"
#include <fstream>

class MeltingPotOnlineTests : public TestFixture<MeltingPotOnlineTests>
{
public:
	TEST_FIXTURE( MeltingPotOnlineTests )
	{
		TEST_CASE( testCatalogue_withoutAuthors );
		TEST_CASE( testCatalogue_withExternalAuthor );
		TEST_CASE( testCatalogue_withContractedAuthor );
		TEST_CASE( testCatalogue_withTwoAuthors );
		TEST_CASE( testCatalogue_withWork );
		TEST_CASE( testCatalogue_withTwoWorksBySameAuthor );
		TEST_CASE( testCatalogue_withManyWorks );
		TEST_CASE( testAddWork_withInexistentAuthor );
		TEST_CASE( testAddWork_withInexistentOriginal );
	}
	/**
	 * The setUp method is automatically called before each test
	 */
	void setUp()
	{
		LibFileSystem::createNetDirectory( "originals" );
	}
	/**
	 * The tearDown method is automatically called after each test
	 */
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "originals" );
	}
	/**
	 * This method creates files used in tests
	 */
	void createOriginalFile( const std::string & name )
	{
		std::string fullname( "originals/" );
		fullname += name;
		std::ofstream os( fullname.c_str() );
		os << "An original file" << std::endl;
		os.close();
	}

	
	void testCatalogue_withoutAuthors()
	{
		MeltingPotOnline business;

		ASSERT_EQUALS(
			"",
			business.catalogue()
		);
	}
	void testCatalogue_withExternalAuthor()
	{
		MeltingPotOnline business;
		business.addAuthor( "An external author", false );

		ASSERT_EQUALS(
			"An external author [external]\n",
			business.catalogue()
		);
	}
	void testCatalogue_withContractedAuthor()
	{
		MeltingPotOnline business;
		business.addAuthor( "A contracted author", true );

		ASSERT_EQUALS(
			"A contracted author [contracted]\n",
			business.catalogue()
		);
	}
	void testCatalogue_withTwoAuthors()
	{
		MeltingPotOnline business;
		business.addAuthor( "An external author", false );
		business.addAuthor( "A contracted author", true );

		ASSERT_EQUALS(
			"An external author [external]\n"
			"A contracted author [contracted]\n",
			business.catalogue()
		);
	}
	void testCatalogue_withWork()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );
		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 121212, "aFile.odt" );

		ASSERT_EQUALS(
			"An author [external]\n"
			"\t121212, 'A work', 'originals/aFile.odt'\n",
			business.catalogue()
		);
	}
	void testCatalogue_withTwoWorksBySameAuthor()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );
		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 111, "aFile.odt" );
		createOriginalFile( "anotherFile.odt" );
		business.addWork( "An author", "Another work", 222, "anotherFile.odt" );

		ASSERT_EQUALS(
			"An author [external]\n"
			"\t111, 'A work', 'originals/aFile.odt'\n"
			"\t222, 'Another work', 'originals/anotherFile.odt'\n",
			business.catalogue()
		);
	}
	void testCatalogue_withManyWorks()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );
		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 123, "aFile.odt" );

		business.addAuthor( "Another author", false );
		createOriginalFile( "anotherFile.odt" );
		business.addWork( "Another author", "Another work", 111, "anotherFile.odt" );
		createOriginalFile( "aThirdFile.odt" );
		business.addWork( "Another author", "A third work", 222, "aThirdFile.odt" );

		ASSERT_EQUALS(
			"An author [external]\n"
			"\t123, 'A work', 'originals/aFile.odt'\n"
			"Another author [external]\n"
			"\t111, 'Another work', 'originals/anotherFile.odt'\n"
			"\t222, 'A third work', 'originals/aThirdFile.odt'\n",
			business.catalogue()
		);
	}
	void testAddWork_withInexistentAuthor()
	{
		MeltingPotOnline business;
		createOriginalFile( "aFile.odt" );

		try
		{
			business.addWork( "An author", "A work", 123, "aFile.odt" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The author does not exist",
				e.what()
			)
		}
	}
	void testAddWork_withInexistentOriginal()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );

		try
		{
			business.addWork( "An author", "A work", 123, "aFile.odt" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"The original file does not exist",
				e.what()
			)
		}
	}
	
};

REGISTER_FIXTURE( MeltingPotOnlineTests )

