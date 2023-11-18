#pragma once
#include "PCH.h"
#include "Utility.h"
#include "Config.h"

template <class T>
class ISingleton
{
public:
	static T* GetSingleton()
	{
		static T singleton;
		return std::addressof(singleton);
	}

protected:
	ISingleton() = default;
	~ISingleton() = default;

	ISingleton(const ISingleton&) = delete;
	ISingleton(ISingleton&&) = delete;
	ISingleton& operator=(const ISingleton&) = delete;
	ISingleton& operator=(ISingleton&&) = delete;
};

namespace Events
{
	inline bool mainMenuClosed = false;

	class EventHandlerForMenu : public ISingleton<EventHandlerForMenu>, public RE::BSTEventSink<RE::MenuOpenCloseEvent>
	{
		RE::BSEventNotifyControl ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>* a_eventSource) override;
	};
}  // namespace Events