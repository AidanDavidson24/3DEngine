#include "EventManager.h"

void neu::EventManager::Initialize()
{
	//
}

void neu::EventManager::Shutdown()
{
	//
}

void neu::EventManager::Update()
{
	//
}

void neu::EventManager::Subscribe(const std::string& name, Event::functionPtr function, GameObject* receiver)
{
	Observer observer;
	observer.receiver = receiver;
	observer.function = function;

	m_events[name].push_back(observer);
}

void neu::EventManager::Unsubscribe(const std::string& name, GameObject* receiver)
{
	// get list of observers for event
	auto& observers = m_events[name];

	// remove observer with matching receiver from observers
	for (auto iter = observers.begin(); iter != observers.end(); iter++)
	{
		if (iter->receiver == receiver)
		{
			observers.erase(iter);
			break;
		}
	}
}

void neu::EventManager::Notify(const Event& event)
{
	auto& observers = m_events[event.name];
	for (auto& observer : observers)
	{
		if (event.receiver == nullptr || event.receiver == observer.receiver)
		{
			observer.function(event);
		}
	}
}
