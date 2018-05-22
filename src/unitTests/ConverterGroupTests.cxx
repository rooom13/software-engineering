#include <fstream>
#include "LibFileSystem.hxx"
#include "MiniCppUnit.hxx"
#include "PdfConverter.hxx"
#include "Converter.hxx"
#include "ConverterGroup.hxx"
#include "HtmlConverter.hxx"

class ConverterGroupTests : public TestFixture<ConverterGroupTests>
{
public:
	TEST_FIXTURE( ConverterGroupTests )
	{
	TEST_CASE( testConvert_withHtmlConverter );
	TEST_CASE( testConvert_withoutConverter );
	TEST_CASE( testConvert_withPrintablePdfConverter );
	TEST_CASE( testConvert_withWatermarkPdfConverter );
	TEST_CASE( testConvert_withHtmlAndPdfConverters );
	TEST_CASE( testConvert_withUnknownConverter);
	
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
	
	void testConvert_withHtmlConverter()
	{
		
		ConverterGroup converter;
		
		createOriginalFile("Original.odt");
		
		converter.add("html");
		converter.convert("originals/Original.odt", "generated/Prefix" );
		
		ASSERT_EQUALS(
			"generated/Prefix [multiple HTML files].war\n", 
			LibFileSystem::listDirectoryInOrder( "generated" )
		);
		
		
		       
		}
		
		void testConvert_withoutConverter()
	{
		
		ConverterGroup converter;
		
		createOriginalFile("Original.odt");

		converter.convert("originals/Original.odt", "generated/Prefix" );
		
		ASSERT_EQUALS(
			"", 	LibFileSystem::listDirectoryInOrder( "generated" )
		);
		
		
		
		}
		
		
	void testConvert_withPrintablePdfConverter(){
		
				
		ConverterGroup converter;
		
		createOriginalFile("Original.odt");
		
		converter.add("pdf_printable");
		
		converter.convert("originals/Original.odt", "generated/Prefix" );
		
		ASSERT_EQUALS(
			"generated/Prefix [printable].pdf\n", 
			LibFileSystem::listDirectoryInOrder( "generated" )
		);
		
		
		
		}
	
	
	void testConvert_withWatermarkPdfConverter()
	{
				
		ConverterGroup converter;
		
		createOriginalFile("Original.odt");
		
		converter.add("pdf_watermark");
		
		converter.convert("originals/Original.odt", "generated/Prefix" );
		
		ASSERT_EQUALS(
			"generated/Prefix [watermark].pdf\n", 
			LibFileSystem::listDirectoryInOrder( "generated" )
		);
		
		
		}
	
	void testConvert_withHtmlAndPdfConverters()
	{
		ConverterGroup converter;
		
		createOriginalFile("Original.odt");
		converter.add("html");
		converter.add("pdf_printable");
		
		converter.convert("originals/Original.odt", "generated/Prefix" );
		
		ASSERT_EQUALS(
			"generated/Prefix [multiple HTML files].war\n"
			"generated/Prefix [printable].pdf\n", 
			LibFileSystem::listDirectoryInOrder( "generated" )
		);
		
		
		}
		void  testConvert_withUnknownConverter(){
			
		ConverterGroup converter;
		
		createOriginalFile("Original.odt");
		

		

		try
		{		converter.add(".doc");
			converter.convert("originals/Original.odt", "generated/Prefix" );
			FAIL( "An exception should be caught!" );
		}
		catch ( std::exception & e )
		{
			ASSERT_EQUALS(
				"This format is not supported",
				e.what()
			)
		}
			
		}
	
};



REGISTER_FIXTURE( ConverterGroupTests )


