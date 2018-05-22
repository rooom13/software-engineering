
#ifndef _SUBJECT_HXX_
#define _SUBJECT_HXX_

#include <vector>
#include "Observer.hxx"

class Subject {

	typedef std::list< Observer * > Observers;
	Observers _observers;

public:
	virtual ~Subject(){
	}

	void addObserver( Observer * observer ) {
		_observers.push_back( observer );
	}

	virtual void notify(const std::string aux, const std::string aux2) {
		

		for ( Observers::iterator it = _observers.begin();
				it != _observers.end(); ++it )
			(*it)->update(aux, aux2);
	}
	
	const std::string listObservers() {
			std::string ObserversList;
	
			for(Observers::iterator it=_observers.begin(); it !=_observers.end(); it++ ){
				ObserversList += (*it)->name()+"\n";
			}
			return ObserversList;
		
		}

};

#endif
