#include "cheat.h"
#include "global.h"
#include "HookManager.h"
#include "events.h"
#include "HotkeyManager.hpp"

#include "features/Debug.h"
#include "features/LuaEditor.h"

using namespace Cheat::Features;

static void GameMain_Update_Hook(void* __this, MethodInfo* method);

void init_cheat()
{
#define INIT_FEATURE(feature) feature::GetInstance()
	INIT_FEATURE(Debug);
	INIT_FEATURE(LuaEditor);
#undef INIT_FEATURE

	HookManager::install(app::GameMain_Update, GameMain_Update_Hook);
}

void GameMain_Update_Hook(void* __this, MethodInfo* method)
{
	SAFE_BEGIN();
	events::GameUpdateEvent();
	HotkeyManager::GetInstance().CheckForKeyPress();
	SAFE_EEND();
	CALL_ORIGIN(GameMain_Update_Hook, __this, method);
}