#pragma once
#include <vector>
#include <algorithm>

class Observer
{
public:
	virtual void update() = 0;
	virtual ~Observer() {}
};


class Observable
{
private:
	std::vector<Observer*> listOfObservers;
public:
	virtual ~Observable() {}

	void addObserver(Observer* observer);

	void removeObserver(Observer* observer);
	void notify();
};

