#ifndef _MELTINGPLOTONLINE_HXX
#define _MELTINGPLOTONLINE_HXX

#include "Model.hxx"
#include <sstream>

#include <stdlib.h>
#include "Collection.hxx"
#include "Author.hxx"
#include <fstream>
#include "ConverterGroup.hxx"
#include "Topic.hxx"
#include "Client.hxx"
#include "MailStub.hxx"
#include "Channel.hxx"

typedef std::list<Collection*> Collections;
typedef std::list<Author*> Authors;
typedef std::list<Topic*> Topics;
typedef std::list<Client*> Clients;
typedef std::list<Channel*> Channels;

class MeltingPotOnline : public Model
{
private: 
	Topics _topics;
        Authors _authors;
        Collections _collections;
		Clients _clients;
        ConverterGroup _convertergroup;
		Channels _channels;
public:
	MeltingPotOnline()
	 :_topics(0)
	{
	_convertergroup.add("html");
	_convertergroup.add("pdf_printable");
	_convertergroup.add("pdf_watermark");
	
	}
	
	~MeltingPotOnline(){ //Destructor, while not empty, delete first of _catalogue and change front pointer
	
		while(!_authors.empty()) delete _authors.front(), _authors.pop_front();	
		
		while(!_collections.empty()) delete _collections.front(), _collections.pop_front();	
		
		while(!_topics.empty()) delete _topics.front(), _topics.pop_front();	
		
		while(!_clients.empty()) delete _clients.front(), _clients.pop_front();	
		
		while(!_channels.empty()) delete _channels.front(), _channels.pop_front();	
		
	}

      
        void addAuthor(const std::string & name, bool contracted){
		
	
		Author *author = new Author(name, contracted);
	
		_authors.push_back(author);

        }

	/*añade un work, a un autor*/	
			
	void addWork(const std::string & authorName,const std::string & workName, int isbn, const std::string & file){
	
		std::string aux = "originals/" + file;
		std::ifstream originalFile (aux.c_str());
		if (originalFile == 0) throw InexistentOrginalFile();
			
		Author & author = findAuthor(authorName);
		author.addWork( workName, isbn,file);   
		std::string common="generated/" + authorName+ " - "+workName;
			

		_convertergroup.convert(aux,common);
		
        }
	
	void addTopic(const std::string & name){
				
		Topic *topic= new Topic(name);
		_topics.push_back(topic);
	
	}

	void addClient(const std::string & name, const std::string & mail){
				
		Client *client= new Client(name, mail);
		_clients.push_back(client);
			
	}

	void addChannel(const std::string & theme, const std::string & name){
				
		Channel *channel= new Channel(theme, name);
		_channels.push_back(channel);
				
	}
				
	//List works
  	std::string  catalogue()const {
               std::string aux = "";
	
		for(Authors::const_iterator it= _authors.begin(); it != _authors.end(); it++ ){
			
			aux += (*it)->description();
		}
		
		return aux;
              
        }
        
	std::string listTopics() const 	{
		std::string topicsList;

		for(Topics::const_iterator it=_topics.begin(); it !=_topics.end(); it++ )
			topicsList += (*it)->name() +"\n";
	
		return topicsList;
		
	}

	const std::string listClients() const{
		std::string clientList;
	
		for(Clients::const_iterator it=_clients.begin(); it !=_clients.end(); it++ )
			clientList += (*it)->name() +" <"+ (*it)->mail()+">\n";
			
		return clientList;
		
	}

	const std::string listThematicChannels() const {
	
		std::string thematicList;
			
		for(Channels::const_iterator it=_channels.begin(); it !=_channels.end(); it++ )
			thematicList += (*it)->name()+"\n\t"+(*it)->theme()+"\n";
		
		return thematicList;
	}


	const std::string listSubscribedToTopic(const std::string & topic)const{
			
		Topic & aTopic = findTopic(topic);
		return aTopic.listClients();
		
	}
        
        /*Delvuelve una referencia del lista de aut*/
        
       
	 Author & findAuthor (const std::string & authorName)const {
			
		for(Authors::const_iterator it= _authors.begin(); it != _authors.end(); it++)
			if((*it)->name().compare(authorName)==0)
				return *(*it);
				
			throw InexistentAuthor();
	}
			
		
	Topic & findTopic(const std::string & name) const{
			
		for(Topics::const_iterator it=_topics.begin(); it !=_topics.end(); it++ )
			if( (*it)->name().compare(name) == 0 )	
				return *(*it);
											
			throw InexsitentTopic();
				
	}

	Client & findClient(const std::string & name)const{
			
		for(Clients::const_iterator it=_clients.begin(); it !=_clients.end(); it++ )
			if( (*it)->name().compare(name) == 0 )	
				return *(*it);
							
			throw InexistentClient();
				
	}


	Channel & findChannel(const std::string & name )const{
				
		for(Channels::const_iterator it=_channels.begin(); it !=_channels.end(); it++ )
			if( (*it)->name().compare(name) == 0 )
				return *(*it);
					
		throw InexistentChannel();
				
	}

		
			
	void associateTopicWithWork(const std::string & topic, const std::string & author, const std::string & work)
	{
		Work * aWork = &(findAuthor(author).findWork(work));
		Topic & aTopic = findTopic(topic);

		aWork->addTopic( aTopic.name());
	
		aTopic.notify(work,author);
	}
		
	void subscribeClientToTopic(const std::string & client, const std::string & topic){
			
		Topic & aTopic = findTopic(topic);
		Client & aClient = findClient(client);
		aTopic.addObserver(&aClient);
			
	}
		
	void subscribeClientToAuthor(const std::string & client, const std::string & author){
			
			Client &aClient = findClient(client);
			Author &aAuthor = findAuthor(author);
			aAuthor.addObserver(&aClient);
	}
			
	void subscribeChannelToAuthor(const std::string & channel, const std::string & author){
			
		Channel &aChannel = findChannel(channel);
		Author &aAuthor = findAuthor(author);
		aAuthor.addObserver(&aChannel);
	}	

	void subscribeChannelToTopic(const std::string & channel, const std::string & topic){
			
		Channel &aChannel = findChannel(channel);
		Topic &aTopic = findTopic(topic);
		aTopic.addObserver(&aChannel);
	}	
			
	
	const std::string rssByChannel(const std::string & name)const{
		
		std::string item,aux;
		Channel &aChannel = findChannel(name);

		return
		"<?xml version='1.0' encoding='UTF-8' ?>\n"
		"<rss version='2.0'>\n"
		"<channel>\n"
		"<title>MeltingPotOnline: "+ aChannel.name()+"</title>\n"
		"<link>http://www.meltingpotonline.com/"+ aChannel.name()+"</link>\n"
		"<description>"+ aChannel.theme()+"</description>\n"+
		aChannel.ListNews()+
		"</channel>\n"
		"</rss>\n";	 
	}
				

	void clientPrefersSms( const std::string & SmsClient, const std::string & numero )const{

		Client &aClient= findClient(SmsClient);
		aClient.mail(numero);
		aClient.mode("sms");
	}


	void clientPrefersWhatsapp( const std::string & whtsClient, const std::string & numero )const{
		
		Client &aClient= findClient(whtsClient);
		aClient.mail(numero);
		aClient.mode("whatts");
	}
};



#endif 

/*

git add unitTests/MeltingPotOnlineTests.cxx 

git add MeltingPotOnline.hxx

git commit -m "GREEN: ItemTests::testTitle_addingTitle"

*/
