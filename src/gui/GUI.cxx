
#include <QApplication>
#include "Model.hxx"
#include "View.hxx"
#include "Controller.hxx"

#include "MeltingPotOnline.hxx"

int main( int argc, char *argv[] ) {
	QApplication app( argc, argv );
	Model * model;
	View view;
	Controller controller;

	MeltingPotOnline business;
	model = &business;

	QObject::connect( model, SIGNAL( modify( const std::string &, const std::string & ) ),
		              &view, SLOT( updateContent( const std::string &, const std::string & ) ) );
	QObject::connect( &view, SIGNAL( actionExecuted( int, const std::string &, const std::string &, const std::string &, const std::string &, int, bool ) ),
		              &controller, SLOT( receiveAction( int, const std::string &, const std::string &, const std::string &, const std::string &, int, bool ) ) );
	QObject::connect( &controller, SIGNAL( addAuthor( const std::string &, bool ) ),
	                  model, SLOT( doAddAuthor( const std::string &, bool ) ) );
	QObject::connect( &controller, SIGNAL( addWork( const std::string &, const std::string &, int ) ),
	                  model, SLOT( doAddWork( const std::string &, const std::string &, int ) ) );
	QObject::connect( &controller, SIGNAL( addTopic( const std::string & ) ),
	                  model, SLOT( doAddTopic( const std::string & ) ) );
	QObject::connect( &controller, SIGNAL( associateTopicWithWork( const std::string &, const std::string &, const std::string & ) ),
	                  model, SLOT( doAssociateTopicWithWork( const std::string &, const std::string &, const std::string & ) ) );
	QObject::connect( &controller, SIGNAL( errorMessage( const QString & ) ),
	                  &view, SLOT( displayError( const QString & ) ) );

	view.show();
	return app.exec();
}

