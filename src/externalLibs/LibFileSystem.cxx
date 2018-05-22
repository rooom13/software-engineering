#include "LibFileSystem.hxx"
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <fstream>

class TraverseDirectory
{

public:

	TraverseDirectory();

	virtual ~TraverseDirectory()
	{
	}

	void Traverse( const std::string & rootname = "", int maxdepth = -1 );

protected:

	virtual void OnFile( const std::string & filename ) { };

	virtual void OnDirectory( const std::string & dirname ) { };

	/**
	* Called from OnDirectory, to indicate that the current directory
	* should not be recursed any further (but do traverse the files inside
	* that
	* directory)
	*/
	void SkipSubdirectories();

	/**
	* Called from OnDirectory, to indicate that the current directory
	* should not be recursed any further, including the files inside
	* that directory)
	*/
	void SkipDirectory();

private:

	void TraverseHelper( DIR* dir, const std::string & dirname, int curdepth, int maxdepth );

	bool IsCurrentOrParentDir( dirent* dirEntry ) const;

	std::string CompleteName( const std::string & currentDirName, dirent* dirEntry ) const;

};


TraverseDirectory::TraverseDirectory()
{
}

// Helper method for TraverseHelper
bool TraverseDirectory::IsCurrentOrParentDir( dirent* dirEntry ) const
{
	static std::string current = ".";
	static std::string parent = "..";
	if ( dirEntry->d_name == current ) return true;
	if ( dirEntry->d_name == parent ) return true;
	return false;
}

std::string TraverseDirectory::CompleteName( const std::string & currentDirName, dirent* dirEntry ) const
{
	bool noDirName = currentDirName == "";
	return noDirName ? dirEntry->d_name : currentDirName + "/" + dirEntry->d_name;
}

void TraverseDirectory::TraverseHelper( DIR* dir, const std::string & currentDirname, int curdepth, int maxdepth )
{
	dirent* dirEntry;
	while ( ( dirEntry = readdir(dir) ) )
	{
		if ( IsCurrentOrParentDir( dirEntry ) )
			continue;

		std::string currentItemName = CompleteName( currentDirname, dirEntry );
		DIR* subdir = opendir( currentItemName.c_str() );
		if ( subdir )
		{
			OnDirectory( currentItemName ); // 'template method'
			if ( curdepth < maxdepth || maxdepth == -1 )
			{
				TraverseHelper( subdir, currentItemName, curdepth+1, maxdepth );
			}
			closedir( subdir );
		}
		else
		{
			OnFile( currentItemName ); // 'template method'
		}
	}
}

void TraverseDirectory::Traverse( const std::string & rootname, int maxdepth )
{
	DIR* dir;

	dir = opendir( rootname == "" ? "." : rootname.c_str() );

	if ( dir )
	{
		OnDirectory( rootname );
		TraverseHelper( dir, rootname, 0, maxdepth );
		closedir( dir );
	}
}


#include <list>
class FileLister : public TraverseDirectory
{

public:

	typedef std::list< std::string > Names;

	void OnFile( const std::string & filename )
	{
		_fileList.push_back( filename );
	}

	std::string orderedList()
	{
		_fileList.sort();
		std::string result;
		for ( Names::iterator it = _fileList.begin(); it != _fileList.end(); ++it )
			result += (*it) + "\n";
		return result;
	}

	const Names & names() const
	{
		return _fileList;
	}

private:

	Names _fileList;

};

#include <sys/stat.h>

std::string LibFileSystem::listDirectoryInOrder( const std::string & dir )
{
	FileLister lister;
	lister.Traverse( dir );
	return lister.orderedList();
}

bool LibFileSystem::directoryExists( const std::string & dir )
{
	struct stat buf;
	return ( stat( dir.c_str(), &buf ) == 0 && S_ISDIR( buf.st_mode ) );
}
bool LibFileSystem::fileExists( const std::string & filename )
{
	struct stat buf;
	return ( stat( filename.c_str(), &buf ) == 0 && S_ISREG( buf.st_mode ) );
}
void LibFileSystem::cleanupDirectory( const std::string & dir  )
{
	FileLister lister;
	lister.Traverse( dir );
	FileLister::Names::const_iterator it = lister.names().begin();
	for ( ; it != lister.names().end(); ++it )
		unlink( it->c_str() );
}

void LibFileSystem::createNetDirectory( const std::string & dir )
{
	if ( directoryExists ( dir ) )
		cleanupDirectory( dir );
	else mkdir( dir.c_str(), 0700 );
}

std::string LibFileSystem::fileContent( const std::string & filename )
{
	std::ifstream is( filename.c_str() );
	std::string result, line;
	while ( std::getline( is, line ) ) result += line + "\n";
	return result;
}


