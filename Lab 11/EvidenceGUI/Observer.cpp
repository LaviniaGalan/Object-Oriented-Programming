#include "Observer.h"

void Observable::addObserver(Observer* observer)
{
	this->listOfObservers.push_back(observer);
}

void Observable::removeObserver(Observer* observer)
{
	auto positionOfObserverInList = std::find(this->listOfObservers.begin(), this->listOfObservers.end(), observer);
	if (positionOfObserverInList != this->listOfObservers.end())
		this->listOfObservers.erase(positionOfObserverInList);
}

void Observable::notify()
{
	for (Observer* observer : this->listOfObservers)
		observer->update();
}
