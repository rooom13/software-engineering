
#ifndef View_hxx
#define View_hxx

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QStringList>
#include <QWidget>

#include <iostream>
#include <map>

class View : public QWidget
{

Q_OBJECT

private:

	QStringList _authors;
	QStringList _topics;
	typedef std::map< QString, QStringList > MapStrings;
	MapStrings _authorWorks;
	MapStrings _workTopics;

	QGridLayout _layout;
	QComboBox _actionBox;
	QLabel _actionLabel;
	QComboBox _authorBox;
	QLabel _authorLabel;
	QComboBox _authorWorkBox;
	QLabel _authorWorkLabel;
	QComboBox _topicBox;
	QLabel _topicLabel;
	QLineEdit _isbnBox;
	QLabel _isbnLabel;
	QLineEdit _textBox;
	QLabel _textLabel;
	QCheckBox _groupBox;
	QLabel _groupLabel;
	QLabel _errorLabel;
	QPushButton _execute;

	std::string nextLine( std::string & str )
	{
		int ix = str.find( '\n' );
		std::string line = str.substr( 0, ix );
		str.erase( 0, ix + 1 );
		return line;
	}

public:

	View()
		: _layout( this )
		, _actionLabel( "Action:" )
		, _authorLabel( "Author:" )
		, _authorWorkLabel( "Work:" )
		, _topicLabel( "Topic:" )
		, _isbnLabel( "ISBN:" )
		, _textLabel( "Name/title:" )
		, _groupLabel( "Contracted:" )
		, _execute( "Execute" )
	{
		_actionBox.addItem( "Create author" );
		_actionBox.addItem( "Create work" );
		_actionBox.addItem( "Create topic" );
		_actionBox.addItem( "Associate topic with work" );

		_layout.addWidget( &_actionLabel, 0, 0 );
		_layout.addWidget( &_actionBox, 0, 1 );
		_layout.addWidget( &_authorLabel, 1, 0 );
		_layout.addWidget( &_authorBox, 1, 1 );
		_layout.addWidget( &_authorWorkLabel, 1, 2 );
		_layout.addWidget( &_authorWorkBox, 1, 3 );
		_layout.addWidget( &_topicLabel, 2, 0 );
		_layout.addWidget( &_topicBox, 2, 1 );
		_layout.addWidget( &_isbnLabel, 2, 2 );
		_layout.addWidget( &_isbnBox, 2, 3 );
		_layout.addWidget( &_textLabel, 3, 0 );
		_layout.addWidget( &_textBox, 3, 1 );
		_layout.addWidget( &_groupLabel, 3, 2 );
		_layout.addWidget( &_groupBox, 3, 3 );
		_layout.addWidget( &_execute, 4, 0 );
		_layout.addWidget( &_errorLabel, 4, 1 );

		QObject::connect( &_execute, SIGNAL( pressed() ),
		                  this, SLOT( execute() ) );
		QObject::connect( &_authorBox, SIGNAL( activated( const QString & ) ),
		                  this, SLOT( authorSelect( const QString & ) ) );
	}

public slots:

	void updateContent( const std::string & catalogue, const std::string & topicList )
	{
		_authors.clear();
		_authorWorks.clear();
		_workTopics.clear();
		_topics.clear();
		_errorLabel.setText( "" );

		std::string copy = catalogue;
		for ( std::string line = nextLine( copy ); !line.empty(); )
		{
			QString author = QString::fromStdString( line );
			_authors.append( author );
			for ( line = nextLine( copy ); !line.empty() && line[0] == '\t'; line = nextLine( copy ) )
			{
				int x = line.find( '\'' );
				int y = line.find( '\'', x + 1 );
				QString work = QString::fromStdString( line.substr( x + 1, y - x - 1 ) );
				_authorWorks[ author ].append( work );
				for ( line = nextLine( copy ); !line.empty() && line[1] == '\t'; line = nextLine( copy ) )
				{
					int ix = line.find( '-' );
					QString topic = QString::fromStdString( line.substr( ix + 2, line.find( '[' ) - ix - 3 ) );
					_workTopics[ work ].append( topic );
				}
			}
		}
		copy = topicList;
		for ( std::string line = nextLine( copy ); !line.empty(); line = nextLine( copy ) )
		{
			QString topic = QString::fromStdString( line );
			_topics.append( topic );
		}
		_authorBox.clear();
		_authorBox.addItems( _authors );
		if ( _authors.size() ) authorSelect( _authors.first() );
		_topicBox.clear();
		_topicBox.addItems( _topics );
	}

	void execute()
	{
		int action = _actionBox.currentIndex();

		std::string author = _authorBox.count() ? _authorBox.currentText().toStdString() : "";
		if ( author.size() ) author = author.substr( 0, author.find( '[' ) - 1 );

		std::string authorWork = _authorWorkBox.count() ? _authorWorkBox.currentText().toStdString() : "";

		std::string topic = _topicBox.count() ? _topicBox.currentText().toStdString() : "";
		if ( topic.size() ) topic = topic.substr( 0, topic.find( '[' ) - 1 );

		int isbn = ( _isbnBox.text().size() ? _isbnBox.text().toInt() : -1 );
		std::string name = _textBox.text().toStdString();
		bool contracted = _groupBox.checkState() == Qt::Checked;
		emit actionExecuted( action, author, authorWork, topic, name, isbn, contracted );
	}

	void authorSelect( const QString & author )
	{
		_authorWorkBox.clear();
		if ( _authorWorks.find( author ) != _authorWorks.end() )
			_authorWorkBox.addItems( _authorWorks[ author ] );
	}

	void displayError( const QString & error )
	{
		_errorLabel.setText( error );
	}

signals:

	void actionExecuted( int action, const std::string & artist, const std::string & track, const std::string & album, const std::string & name, int isbn, bool group );

};

#endif
