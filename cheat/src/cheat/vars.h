#pragma once

#include "ConfigEntry.hpp"

class Vars final : public Singleton<Vars>
{
public:
	Vars() = default;

	// CONFIG_ENTRY_HOTKEY(bool, m_LuaEditor, false, Hotkey());
};
