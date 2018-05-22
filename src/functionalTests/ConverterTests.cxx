#include <fstream>
#include "LibFileSystem.hxx"
#include "MiniCppUnit.hxx"
#include "MeltingPotOnline.hxx"

class ConverterTests : public TestFixture<ConverterTests>
{
public:
	TEST_FIXTURE( ConverterTests )
	{
		TEST_CASE( testConvertersByDefault_withoutOriginals );
		TEST_CASE( testConvertersByDefault_withOneOriginal );
		//TEST_CASE( testOptionalConverterWithFile_withOneOriginal );
	}

	/**
	 * The setUp method is automatically called before each test
	 */
	void setUp()
	{
		LibFileSystem::createNetDirectory( "config" );
		LibFileSystem::createNetDirectory( "generated" );
		LibFileSystem::createNetDirectory( "originals" );
	}
	/**
	 * The tearDown method is automatically called after each test
	 */
	void tearDown()
	{
		LibFileSystem::cleanupDirectory( "config" );
		LibFileSystem::cleanupDirectory( "generated" );
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
	
	void testConvertersByDefault_withoutOriginals()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );

		ASSERT_EQUALS(
			"", 
			LibFileSystem::listDirectoryInOrder( "generated" )
		);
	}
	void testConvertersByDefault_withOneOriginal()
	{
		MeltingPotOnline business;
		business.addAuthor( "An author", false );
		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 123, "aFile.odt" );

		ASSERT_EQUALS(
			"generated/An author - A work [multiple HTML files].war\n"
			"generated/An author - A work [printable].pdf\n"
			"generated/An author - A work [watermark].pdf\n",
			LibFileSystem::listDirectoryInOrder( "generated" )
		);
	}
	/*void testOptionalConverterWithFile_withOneOriginal()
	{
		std::ofstream config( "config/config.txt" );
		config << "pdf_mark\n";
		config << "html\n";
		config.close();

		MeltingPotOnline business( "config/config.txt" );
		business.addAuthor( "An author", false );
		createOriginalFile( "aFile.odt" );
		business.addWork( "An author", "A work", 123, "aFile.odt" );

		ASSERT_EQUALS(
			"generated/An author - A work [multiple HTML files].war\n"
			"generated/An author - A work [watermark].pdf\n",
			LibFileSystem::listDirectoryInOrder( "generated" )
		);
	}
	*/
};

REGISTER_FIXTURE( ConverterTests )


