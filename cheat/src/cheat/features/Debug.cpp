#include "Debug.h"
#include "HookManager.h"
#include "Utils.h"
#include "game-utils.hpp"
#include "events.h"

namespace Cheat::Features
{
	Debug::Debug()
	{
		events::GameUpdateEvent += MY_METHOD_HANDLER(Debug::OnGameUpdate);

		HookManager::install(app::LuaDLL_lua_ptrtostring, LuaDLL_lua_ptrtostring_Hook);
		HookManager::install(app::LuaDLL_lua_tostring, LuaDLL_lua_tostring_Hook);
		HookManager::install(app::LuaDLL_luaL_loadbuffer, LuaDLL_luaL_loadbuffer_Hook);
		HookManager::install(app::LuaDLL_luaL_loadstring, LuaDLL_luaL_loadstring_Hook);
		HookManager::install(app::LuaDLL_luaL_dostring, LuaDLL_luaL_dostring_Hook);

		HookManager::install(app::LuaState_DoString, LuaState_DoString_Hook);
		HookManager::install(app::LuaState_DoString_1, LuaState_DoString_1_Hook);
		HookManager::install(app::LuaState_LuaLoadBuffer, LuaState_LuaLoadBuffer_Hook);
		HookManager::install(app::LuaStatePtr_LuaLoadBuffer, LuaStatePtr_LuaLoadBuffer_Hook);
		HookManager::install(app::LuaState_LuaLoadBuffer_1, LuaState_LuaLoadBuffer_1_Hook);
		LOG_DEBUG("Hooked Lua functions");
	}

	void Debug::OnGameUpdate()
	{
	}

	app::String* Debug::LuaDLL_lua_ptrtostring_Hook(void* str, int32_t len, MethodInfo* method)
	{
		// LOG_DEBUG("LuaDLL_lua_ptrtostring_Hook");
		return CALL_ORIGIN(LuaDLL_lua_ptrtostring_Hook, str, len, method);
	}
	app::String* Debug::LuaDLL_lua_tostring_Hook(void* luaState, int32_t index, MethodInfo* method)
	{
		// LOG_DEBUG("LuaDLL_lua_tostring_Hook");
		auto ret = CALL_ORIGIN(LuaDLL_lua_tostring_Hook, luaState, index, method);
		// LOG_DEBUG("%s", il2cppi_to_string(ret).c_str());

		return ret;
	}
	int32_t Debug::LuaDLL_luaL_loadbuffer_Hook(void* luaState, app::Byte__Array* buff, int32_t size, app::String* name, MethodInfo* method)
	{
		LOG_DEBUG("LuaDLL_luaL_loadbuffer_Hook");
		return CALL_ORIGIN(LuaDLL_luaL_loadbuffer_Hook, luaState, buff, size, name, method);
	}
	int32_t Debug::LuaDLL_luaL_loadstring_Hook(void* luaState, app::String* chunk, MethodInfo* method)
	{
		LOG_DEBUG("LuaDLL_luaL_loadstring_Hook");
		return CALL_ORIGIN(LuaDLL_luaL_loadstring_Hook, luaState, chunk, method);
	}
	bool Debug::LuaDLL_luaL_dostring_Hook(void* luaState, app::String* chunk, MethodInfo* method)
	{
		LOG_DEBUG("LuaDLL_luaL_dostring_Hook");
		return CALL_ORIGIN(LuaDLL_luaL_dostring_Hook, luaState, chunk, method);
	}

	void Debug::LuaState_DoString_Hook(app::LuaState* __this, app::String* chunk, app::String* chunkName, MethodInfo* method)
	{
		LOG_DEBUG("LuaState_DoString_Hook");
		CALL_ORIGIN(LuaState_DoString_Hook, __this, chunk, chunkName, method);
	}
	app::Object* Debug::LuaState_DoString_1_Hook(app::LuaState* __this, app::String* chunk, app::String* chunkName, MethodInfo* method)
	{
		LOG_DEBUG("LuaState_DoString_1_Hook");
		return CALL_ORIGIN(LuaState_DoString_1_Hook, __this, chunk, chunkName, method);
	}
	void Debug::LuaState_LuaLoadBuffer_Hook(app::LuaState* __this, app::Byte__Array* buffer, app::String* chunkName, MethodInfo* method)
	{
		LOG_DEBUG("LuaState_LuaLoadBuffer_Hook");
		CALL_ORIGIN(LuaState_LuaLoadBuffer_Hook, __this, buffer, chunkName, method);
	}
	int32_t Debug::LuaStatePtr_LuaLoadBuffer_Hook(app::LuaStatePtr* __this, app::Byte__Array* buff, int32_t size, app::String* name, MethodInfo* method)
	{
		LOG_DEBUG("LuaStatePtr_LuaLoadBuffer_Hook");
		return CALL_ORIGIN(LuaStatePtr_LuaLoadBuffer_Hook, __this, buff, size, name, method);
	}
	app::Object* Debug::LuaState_LuaLoadBuffer_1_Hook(app::LuaState* __this, app::Byte__Array* buffer, app::String* chunkName, MethodInfo* method)
	{
		LOG_DEBUG("LuaState_LuaLoadBuffer_1_Hook");
		return CALL_ORIGIN(LuaState_LuaLoadBuffer_1_Hook, __this, buffer, chunkName, method);
	}
}
