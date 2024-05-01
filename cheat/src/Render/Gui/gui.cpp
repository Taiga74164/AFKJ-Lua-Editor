#include "gui.h"
#include "global.h"
#include "imgui.h"
#include "Utils.h"
#include "utils/gui-util.hpp"
#include "cheat/features/LuaEditor.h"

void Gui::Render()
{
	auto& luaEditor = Cheat::Features::LuaEditor::GetInstance();
	luaEditor.DrawExternal();
}