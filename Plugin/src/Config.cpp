#include "Config.h"

namespace Config
{
	void Apply();

	void ReadIni()
	{
		std::filesystem::path path = std::filesystem::path(fmt::format("Data/SFSE/Plugins/{}.ini", Plugin::NAME));
		if (!std::filesystem::exists(path))
			return;

		auto config = toml::parse_file(path.string());
		auto items = config["Config"]["Items"].as_array();
		if (!items) {
			//Utility::Notification(fmt::format("ERROR: can't load toml file:{}", path.string())); aa
			return;
		}

		FormIDs.clear();
		for (const auto& item : *items) {
			if (!item.is_string()) {
				//Utility::Notification(fmt::format("  toml format error: skip")); aa
				continue;
			}
			FormIDs.push_back(item.value_or(""));
			//Utility::Notification(fmt::format("  toml element: {}", item.value_or(""))); aa
				//item.as_integer());
		}

		Apply();
	}

	void Apply()
	{
		for (auto formID : FormIDs) {
			auto form = RE::TESForm::LookupByEditorID(formID.c_str());
			if (!form) {
				//Utility::Notification(fmt::format("form: {} was not found.", formID)); aa
				continue;
			}
			//Utility::Notification(fmt::format("before: form: {}'s Playable flag is {}.", form->GetFormEditorID(), form->GetPlayable()));
			form->SetPlayable(true);
			//Utility::Notification(fmt::format("after : form: {}'s Playable flag is {}.", form->GetFormEditorID(), form->GetPlayable()));
			//Utility::Notification(fmt::format("form: {}'s formtype is {}. playable-flag is {}", form->GetFormEditorID(), form->GetFormType(), form->GetPlayable())); aa
		}
	}
}
