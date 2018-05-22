#ifndef MailStub_hxx
#define MailStub_hxx

#include <string>
#include <list>

class MessageLog
{

	typedef std::list< std::string > SentMessages;

public:

	void addMessage( const std::string& message )
	{
		_sent.push_back( message );
	}

	//! return the concatenation of all messages sent,
	//! in alphabetical order
	std::string log()
	{
		_sent.sort();
		SentMessages::const_iterator it = _sent.begin();
		std::string result;
		for ( ; it != _sent.end(); ++it )
		{
			result += (*it) + "\n";
		}
		return result;
	}

	void removeSent()
	{
		_sent.clear();
	}

private:

	SentMessages _sent;

};

// --------------------------------------------------------------------------------

class MailStub : public MessageLog
{

	//! private constructor, implementing the Singleton pattern
	MailStub()	{}

	MailStub( const MailStub& )	{}

public:

	static MailStub& theInstance()
	{
		static MailStub _theInstance;
		return _theInstance;
	}

	void sendMail( const std::string& to, const std::string& subject )
	{
		std::string mail= "To: " + to + "\n";
		mail += "Subject: " + subject + "\n";

		addMessage( mail );
	}

	//! return the concatenation of all messages sent,
	//! in alphabetical order
	std::string sentMails()
	{
		return log();
	}

};

// --------------------------------------------------------------------------------

class SmsStub : public MessageLog
{

	//! private constructor, implementing the Singleton pattern
	SmsStub() {} 
	SmsStub( const SmsStub&) {} 

public:

	static SmsStub& theInstance()
	{
		static SmsStub _theInstance;
		return _theInstance;
	}

	void sendSms( const std::string& phone, const std::string& text )
	{
		std::string message( "SMS to ");
		message += phone + ": " + text;
		addMessage( message );
	}

	//! return the concatenation of all messages sent,
	//! in alphabetical order
	std::string sentMessages()
	{
		return log();
	}

};

// --------------------------------------------------------------------------------

class WhatsappStub : public MessageLog
{

	//! private constructor, implementing the Singleton pattern
	WhatsappStub() {} 
	WhatsappStub( const WhatsappStub&) {} 

public:

	static WhatsappStub& theInstance()
	{
		static WhatsappStub _theInstance;
		return _theInstance;
	}

	void sendWhatsapp( const std::string& phone, const std::string& text )
	{
		std::string message( "Whatsapp to ");
		message += phone + ": " + text;
		addMessage( message );
	}

	//! return the concatenation of all messages sent,
	//! in alphabetical order
	std::string sentMessages()
	{
		return log();
	}

};

#endif
