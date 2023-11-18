#pragma once
#include "PCH.h"

namespace Utility
{
	//common
	inline REL::Relocation<__int64 (*)(double, char*, ...)> ExecuteCommand{ REL::ID(166307) };  // From Console-Command-Runner-SF

	void        Notification(std::string message);
	void        ExecuteCommandString(std::string command, std::string displayPrefix = "  ConsoleCommand: ");
	void        ExecuteCommandStringOnFormID(int formID, std::string subCommand);
	std::string num2hex(uint32_t formID, bool prefixOn = true, bool paddingOn = false);
	uint32_t    hex2num(std::string formID);

	//common
	bool             InGameScene();
	std::vector<int> DecomposeSlot(uint32_t value);
	bool             HasSlot(uint32_t value, int slot);
}