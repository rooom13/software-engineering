#include <fstream>
#include "LibFileSystem.hxx"
#include "MiniCppUnit.hxx"
#include "HtmlConverter.hxx"
#include "Converter.hxx"
#include "libLibreOffice2Html.hxx"


class HtmlConverterTests : public TestFixture<HtmlConverterTests>
{
public:
	TEST_FIXTURE( HtmlConverterTests )
	{
		TEST_CASE( testConvert_generateFile );
		TEST_CASE( testConvert_generateContent);
		TEST_CASE( testConvert_withInexistentOriginal );
		TEST_CASE( testConvert_polymorphicCall);

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
	
	
	// 
	void testConvert_generateFile()
	{
		HtmlConverter converter;
		createOriginalFile("Original.odt");
		converter.convert("originals/Original.odt", "generated/Prefix" );
		
		ASSERT_EQUALS(
			"generated/Prefix [multiple HTML files].war\n", 
			LibFileSystem::listDirectoryInOrder( "generated" )
		);
	}
	
	void testConvert_generateContent()
	{
		HtmlConverter converter;
		createOriginalFile("Original.odt");
		
		converter.convert("originals/Original.odt", "generated/Prefix" );
		
		OO_WarGeneration( "originals/Original.odt" , "generated/Prefix [multiple HTML files].war\n" );

		ASSERT_EQUALS(
			"War file generated from 'originals/Original.odt'\n", 
			LibFileSystem::fileContent( "generated/Prefix [multiple HTML files].war\n" )
		);
		
	}
	
	
		void testConvert_withInexistentOriginal()
	{
		
		HtmlConverter converter;

		try
		{
			converter.convert("originals/Original.odt", "generated/Prefix" );
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
	
		void testConvert_polymorphicCall()
			{
			
			Converter * converter = new HtmlConverter();
			
			createOriginalFile("Original.odt");
			converter->convert("originals/Original.odt", "generated/Prefix" );
		
			ASSERT_EQUALS(
			"generated/Prefix [multiple HTML files].war\n", 
			LibFileSystem::listDirectoryInOrder( "generated" ) 
			);
			
			delete converter;
			
			}
			
};

REGISTER_FIXTURE( HtmlConverterTests )


