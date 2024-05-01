#include "cheat.h"
#include "global.h"
#include "HookManager.h"
#include "events.h"
#include "HotkeyManager.hpp"

#include "features/Debug.h"
#include "features/LuaEditor.h"

using namespace Cheat::Features;

static void NetworkManager_OnUpdate_Hook(void* __this, float deltaTime, MethodInfo* method);

void init_cheat()
{
#define INIT_FEATURE(feature) feature::GetInstance()
	// INIT_FEATURE(Debug);
	INIT_FEATURE(LuaEditor);
#undef INIT_FEATURE

	HookManager::install(app::NetworkManager_OnUpdate, NetworkManager_OnUpdate_Hook);
}

void NetworkManager_OnUpdate_Hook(void* __this, float deltaTime, MethodInfo* method)
{
	SAFE_BEGIN();
	events::GameUpdateEvent();
	HotkeyManager::GetInstance().CheckForKeyPress();
	SAFE_EEND();
	CALL_ORIGIN(NetworkManager_OnUpdate_Hook, __this, deltaTime, method);
}