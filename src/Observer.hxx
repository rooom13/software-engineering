
#ifndef _OBSERVER_HXX_
#define _OBSERVER_HXX_

class Observer {

	
public:
	virtual ~Observer(){}
	virtual void update(const std::string & t, const std::string & n) = 0;
	virtual const std::string & name() const = 0;
};

#endif
