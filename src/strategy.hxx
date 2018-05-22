#ifndef _STRATEGY_HXX
#define _STRATEGY_HXX
#include "MailStub.hxx"


class Strategy
{
	
public:
virtual ~Strategy(){}	
virtual void send(const std::string  & to, const std::string  & subject)=0;
		
};


class SendMail : public Strategy
{
	
public:
	SendMail(){}
	void send(const std::string  & to, const std::string  & subject){

	MailStub::theInstance().sendMail(to, subject );

	}
		
};

class SendWhatts: public Strategy{
	
public:
	SendWhatts(){}
	void send(const std::string  & to, const std::string  & subject){
	WhatsappStub::theInstance().sendWhatsapp(to, subject );
	
	}
		
};

class SendSms: public Strategy
{
	
public:	
	SendSms(){}
	void send(const std::string  & to, const std::string  & subject){
	SmsStub::theInstance().sendSms(to, subject );

	}
		
};
#endif
