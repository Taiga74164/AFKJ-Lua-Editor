// Generated C++ file by Il2CppInspector - http://www.djkaty.com - https://github.com/djkaty
// Target Unity version: 2021.2.0+

// ******************************************************************************
// * IL2CPP application-specific method definition addresses and signatures
// ******************************************************************************
using namespace app;

DO_APP_FUNC(0x017ACF30, void, NetworkManager_OnUpdate, (void/*NetworkManager*/* __this, float deltaTime, MethodInfo* method));

DO_APP_FUNC(0x0349EAD0, String*, Marshal_PtrToStringAnsi, (void* ptr, MethodInfo* method));
DO_APP_FUNC(0x0349EB90, String*, Marshal_PtrToStringUni, (void* ptr, MethodInfo* method));

DO_APP_FUNC(0x033C04A0, String*, Encoding_GetString_2, (Encoding* __this, Byte__Array* bytes, MethodInfo* method));
DO_APP_FUNC_METHODINFO(0x05C06438, Encoding_GetString_2__MethodInfo);
DO_APP_FUNC(0x033C08F0, Encoding*, Encoding_get_UTF8, (MethodInfo* method));

DO_APP_FUNC(0x00B62950, float, IGameTime_get_timeScale, (MethodInfo * method));
DO_APP_FUNC(0x00B629D0, void, IGameTime_set_timeScale, (float value, MethodInfo * method));

DO_APP_FUNC(0x014C99F0, String *, LuaDLL_lua_ptrtostring, (void * str, int32_t len, MethodInfo * method));
DO_APP_FUNC(0x014C9AF0, String *, LuaDLL_lua_tostring, (void * luaState, int32_t index, MethodInfo * method));
DO_APP_FUNC(0x014CC230, int32_t, LuaDLL_luaL_loadbuffer, (void * luaState, Byte__Array * buff, int32_t size, String * name, MethodInfo * method));
DO_APP_FUNC(0x014CC440, int32_t, LuaDLL_luaL_loadstring, (void* luaState, String* chunk, MethodInfo* method));
DO_APP_FUNC(0x014CC9E0, bool, LuaDLL_luaL_dostring, (void * luaState, String * chunk, MethodInfo * method));

// Lua Editor
DO_APP_FUNC(0x014CC340, int32_t, LuaDLL_luaL_loadbufferx, (void* L, Byte__Array* buff, int64_t size, String* name, String* mode, MethodInfo* method));
DO_APP_FUNC(0x014CF650, int32_t, LuaDLL_tolua_error, (void* L, String* msg, MethodInfo* method));
DO_APP_FUNC(0x014C8B20, int32_t, LuaDLL_lua_pcall, (void* luaState, int32_t nArgs, int32_t nResults, int32_t errfunc, MethodInfo* method));
DO_APP_FUNC(0x014C7380, int64_t, LuaDLL_lua_tointegerx, (void* luaState, int32_t idx, int32_t* pisnum, MethodInfo* method));
DO_APP_FUNC(0x014C7250, double, LuaDLL_lua_tonumberx, (void* L, int32_t idx, void* pisnum, MethodInfo* method));
DO_APP_FUNC(0x014CF210, bool, LuaDLL_tolua_toboolean, (void* luaState, int32_t index, MethodInfo* method));
DO_APP_FUNC(0x014C6EC0, LuaTypes__Enum, LuaDLL_lua_type, (void* luaState, int32_t index, MethodInfo* method));
DO_APP_FUNC(0x014C7570, void*, LuaDLL_lua_tolstring, (void* luaState, int32_t index, int32_t* strLen, MethodInfo* method));