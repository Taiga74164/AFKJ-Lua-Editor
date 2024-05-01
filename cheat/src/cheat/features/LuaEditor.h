#pragma once
#include "Singleton.h"
#include "global.h"
#include "ConfigEntry.hpp"
#include "TextEditor.h"

#include <lua.hpp>

namespace Cheat::Features
{
	class LuaEditor : public Singleton<LuaEditor>
	{
	public:
		LuaEditor();

		CONFIG_ENTRY(std::string, f_Code, "");

		void DrawExternal();
		void OpenEditor();
		void CloseEditor();
		void ToggleEditor();

	private:
		void Compile(const std::string& code);
		void ApplyEditorChanges();

		void OnGameUpdate();

		bool m_Enabled;
		TextEditor m_Editor;
		lua_State* m_State;
		bool m_TextChanged;
	};
}
