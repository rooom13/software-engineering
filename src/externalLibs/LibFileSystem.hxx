
#ifndef LibFileSystem_hxx
#define LibFileSystem_hxx

#include <string>

class LibFileSystem
{
public:

	static void cleanupDirectory( const std::string & dir );

	static std::string listDirectoryInOrder( const std::string & dir );

	static void createNetDirectory( const std::string & dir );

	static bool directoryExists( const std::string & dir );

	static bool fileExists( const std::string & filename );

	static std::string fileContent( const std::string & filename );

};


#endif
