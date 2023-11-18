#include "PCH.h"
#include "Event.h"
#include "DKUtil/Hook.hpp"

// SFSE message listener, use this to do stuff at specific moments during runtime
void Listener(SFSE::MessagingInterface::Message* message) noexcept
{
	if (message->type == SFSE::MessagingInterface::kPostLoad) {
		RE::UI::GetSingleton()->RegisterSink(Events::EventHandlerForMenu::GetSingleton());
	}
}

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* a_sfse)
{
#ifndef NDEBUG
	MessageBoxA(NULL, "Loaded. You can now attach the debugger or continue execution.", Plugin::NAME.data(), NULL);
#endif

	SFSE::Init(a_sfse, false);
	DKUtil::Logger::Init(Plugin::NAME, std::to_string(Plugin::Version));
	INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);

	if (const auto messaging{ SFSE::GetMessagingInterface() }; !messaging->RegisterListener(Listener))
		return false;

	return true;
}
