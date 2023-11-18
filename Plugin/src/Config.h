#pragma once
#include "PCH.h"
#include "Utility.h"

namespace Config
{
	inline std::vector<std::string> FormIDs;
	void                            ReadIni();
	void                            Apply();
}