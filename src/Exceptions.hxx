#ifndef _EXCEPTIONS_HXX
#define _EXCEPTIONS_HXX

class InexistentWork :public std::exception
{
	public:
		const char * what() const throw()
		{ 
			return  "The work does not exist";
		}
};

class InexistentAuthor :public std::exception
{
	public:
		const char * what() const throw()
		{ 
			return  "The author does not exist";
		}
};

class InexistentOrginalFile :public std::exception
{
	public:
		const char * what() const throw()
		{ 
			return  "The original file does not exist";
		}
};

class UnknownFormat :public std::exception
{
	public:
		const char * what() const throw()
		{ 
			return  "This format is not supported";
		}
};


class InexsitentTopic :public std::exception
{
	public:
		const char * what() const throw()
		{ 
			return  "The topic does not exist";
		}
};

class InexistentClient :public std::exception
{
	public:
		const char * what() const throw()
		{ 
			return  "The client does not exist";
		}
};

class InexistentChannel :public std::exception
{
	public:
		const char * what() const throw()
		{ 
			return  "The thematic channel does not exist"; 
		}
};

#endif
