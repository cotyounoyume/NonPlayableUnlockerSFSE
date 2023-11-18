#include "Utility.h"

namespace Utility
{
	void ExecuteCommandString(std::string command, std::string displayPrefix)
	{
		ExecuteCommand(0, command.data());
		Utility::Notification(displayPrefix + command);
	}

	void ExecuteCommandStringOnFormID(int formID, std::string subCommand)
	{
		std::string command = fmt::format("{}.{}", num2hex(formID), subCommand);
		ExecuteCommandString(command);
	}

	void Notification(std::string message)
	{
		bool NotificationOn = false;
		bool InfoOn = false;
		//NotificationOn = true;
		InfoOn = true;
		if (NotificationOn)
			RE::DebugNotification(message.c_str());
		if (InfoOn)
			logger::info("{}", message);
	}

	bool InGameScene()
	{
		auto* player = RE::PlayerCharacter::GetSingleton();
		if (player == nullptr)
			return false;
		if (RE::UI::GetSingleton()->IsMenuOpen("Console"))
			return false;
		if (RE::UI::GetSingleton()->IsMenuOpen("PauseMenu") || RE::UI::GetSingleton()->IsMenuOpen("FaderMenu") || RE::UI::GetSingleton()->IsMenuOpen("LoadingMenu") || RE::UI::GetSingleton()->IsMenuOpen("MainMenu"))
			return false;

		return true;
	}

	std::vector<int> DecomposeSlot(uint32_t value)
	{
		std::vector<int> powers;

		while (value > 0) {
			int logVal = static_cast<int>(std::log2(value));
			powers.push_back(logVal);
			value -= static_cast<unsigned int>(std::pow(2, logVal));
		}

		return powers;
	}

	bool HasSlot(uint32_t value, int slot)
	{
		return value & (1 << slot);
	}

	std::string num2hex(uint32_t formID, bool prefixOn, bool paddingOn)
	{
		std::string result = paddingOn ? fmt::format("{:08x}", formID) : fmt::format("{:x}", formID);
		result = prefixOn ? "0x" + result : result;
		return result;
	}

	uint32_t hex2num(std::string formID)
	{
		int intValue;
		try {
			intValue = std::stoi(formID, 0, 16);  // ベース16（16進数）で変換
			return intValue;
		} catch (const std::invalid_argument& ia) {
			return 0;
		} catch (const std::out_of_range& oor) {
			return 0;
		}
		return 0;
	}
}