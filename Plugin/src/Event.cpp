#include "Event.h"

namespace Events
{
	RE::BSEventNotifyControl EventHandlerForMenu::ProcessEvent(const RE::MenuOpenCloseEvent& a_event, RE::BSTEventSource<RE::MenuOpenCloseEvent>*)
	{
		Utility::Notification(fmt::format("Menu: name:{}, opening:{}", a_event.menuName.c_str(), a_event.opening));
		//for future release
		if (a_event.menuName == "MainMenu" and !a_event.opening) {
			mainMenuClosed = true;
		}
		if (a_event.menuName == "LoadingMenu" and !a_event.opening) {
			if (mainMenuClosed) {
				Config::ReadIni();
			}
		}
		return RE::BSEventNotifyControl::kContinue;
	}
}