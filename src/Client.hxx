#ifndef _CLIENT_HXX
#define _CLIENT_HXX
#include "MailStub.hxx"
#include "Observer.hxx"
#include "strategy.hxx"


class Client: public Observer {
	
private: 

	std::string _name;
	std::string _mail;
	std::string _number;
	std::string _mode;
	Strategy *_strategy=NULL;
	
	
public:
	Client()
			
		: _name("-- Untitled --"),
		_mail("-- unmailed --"),
		_number("-No_number-"),
		_mode("mail")
	{}
	
	Client(const std::string & name, const std::string & mail)
			
	{
	_name=name;
	_mail=mail;
	
	}
	
	~Client(){

	}

	const std::string & name()const{
		return _name;
	}
	
	void name( const std::string  & name){
		_name = name;
	}

	void number( const std::string  & number){
		_number = number;
	}
	
	const std::string & mail()const{
		return _mail;
	}
	
	void mail( const std::string  & mail){
		_mail = mail;
	}

	void mode( const std::string  & mode){
		_mode = mode;
	}

	
	void update(const std::string & t,const std::string & n ) {
		
		std::string aux=t+" by "+n;
		
		if (_mode == "whatts"	){
		const std:: string to =  mail();
		const std:: string subject = "[MeltingPot] new work "+ aux;
		_strategy = new SendWhatts();
		_strategy->send(to, subject);
		
		}
		else if (_mode =="sms" ){
		const std:: string to =  mail();
		const std:: string subject = "[MeltingPot] new work "+ aux;
		_strategy = new SendSms();
		_strategy->send(to, subject);
		}
		else {
		const std:: string to = name()+ " <" + mail()+">";
		const std:: string subject = "new work "+ aux;
		_strategy = new SendMail();
		_strategy->send(to, subject);
		}

		delete _strategy;
		
		}
		
		
		
};

#endif
