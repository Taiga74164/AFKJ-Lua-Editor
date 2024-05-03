#pragma once
#include "Singleton.h"
#include "global.h"

namespace Cheat::Features
{
	class Debug : public Singleton<Debug>
	{
	public:
		Debug();

		void OnGameUpdate();

	private:
		static app::String* LuaDLL_lua_ptrtostring_Hook(void* str, int32_t len, MethodInfo* method);
		static app::String* LuaDLL_lua_tostring_Hook(void* luaState, int32_t index, MethodInfo* method);
		static int32_t LuaDLL_luaL_loadbuffer_Hook(void* luaState, app::Byte__Array* buff, int32_t size, app::String* name, MethodInfo* method);
		static int32_t LuaDLL_luaL_loadstring_Hook(void* luaState, app::String* chunk, MethodInfo* method);
		static bool LuaDLL_luaL_dostring_Hook(void* luaState, app::String* chunk, MethodInfo* method);

		static void LuaState_DoString_Hook(app::LuaState* __this, app::String* chunk, app::String* chunkName, MethodInfo* method);
		static app::Object* LuaState_DoString_1_Hook(app::LuaState* __this, app::String* chunk, app::String* chunkName, MethodInfo* method);
		static void LuaState_LuaLoadBuffer_Hook(app::LuaState* __this, app::Byte__Array* buffer, app::String* chunkName, MethodInfo* method);
		static int32_t LuaStatePtr_LuaLoadBuffer_Hook(app::LuaStatePtr* __this, app::Byte__Array* buff, int32_t size, app::String* name, MethodInfo* method);
		static app::Object* LuaState_LuaLoadBuffer_1_Hook(app::LuaState* __this, app::Byte__Array* buffer, app::String* chunkName, MethodInfo* method);
	};
}
