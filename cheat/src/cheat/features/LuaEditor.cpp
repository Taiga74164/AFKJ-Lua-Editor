#include "LuaEditor.h"
#include "HookManager.h"
#include "Utils.h"
#include "game-utils.hpp"
#include "events.h"

// https://www.lua.org/manual/5.3/manual.html
namespace Cheat::Features
{
#pragma region types
	static int (*luaL_loadbufferx_p) (lua_State* L, const char* buff, int size, const char* name, const char* mode) = 0;
	typedef decltype(luaL_loadbufferx_p) luaL_loadbufferx_t;

	static int (*tolua_error_p) (lua_State* L, const char* msg) = 0;
	typedef decltype(tolua_error_p) tolua_error_t;

	static int (*lua_pcall_p) (lua_State* L, int nArgs, int nResults, int errfunc) = 0;
	typedef decltype(lua_pcall_p) lua_pcall_t;

	static decltype(lua_tointegerx) (*lua_tointegerx_p) = 0;
	typedef decltype(lua_tointegerx) (*lua_tointegerx_t);

	static decltype(lua_tonumberx) (*lua_tonumberx_p) = 0;
	typedef decltype(lua_tonumberx) (*lua_tonumberx_t);

	static decltype(lua_tolstring) (*lua_tolstring_p) = 0;
	typedef decltype(lua_tolstring) (*lua_tolstring_t);

	static decltype(lua_toboolean) (*lua_toboolean_p) = 0;
	typedef decltype(lua_toboolean) (*lua_toboolean_t);

	static decltype(lua_type) (*lua_type_p) = 0;
	typedef decltype(lua_type) (*lua_type_t);
#pragma endregion

	LuaEditor::LuaEditor()
	{
		m_TextChanged = false;

		auto xlua = GetModuleHandleW(L"igame.dll");
		if (xlua == nullptr)
			xlua = GetModuleHandleW(L"igame.dll");

		luaL_loadbufferx_p = (luaL_loadbufferx_t)GetProcAddress(xlua, "luaL_loadbufferx");
		if (luaL_loadbufferx_p == nullptr)
			luaL_loadbufferx_p = (luaL_loadbufferx_t)app::LuaDLL_tolua_error;
		tolua_error_p = (tolua_error_t)GetProcAddress(xlua, "tolua_error");
		if (tolua_error_p == nullptr)
			tolua_error_p = (tolua_error_t)app::LuaDLL_tolua_error;
		lua_pcall_p = (lua_pcall_t)GetProcAddress(xlua, "lua_pcall");
		if (lua_pcall_p == nullptr)
			lua_pcall_p = (lua_pcall_t)app::LuaDLL_lua_pcall;
		lua_tointegerx_p = (lua_tointegerx_t)GetProcAddress(xlua, "lua_tointegerx");
		if (lua_tointegerx_p == nullptr)
			lua_tointegerx_p = (lua_tointegerx_t)app::LuaDLL_lua_tointegerx;
		lua_tonumberx_p = (lua_tonumberx_t)GetProcAddress(xlua, "lua_tonumberx");
		if (lua_tonumberx_p == nullptr)
			lua_tonumberx_p = (lua_tonumberx_t)app::LuaDLL_lua_tonumberx;
		lua_toboolean_p = (lua_toboolean_t)GetProcAddress(xlua, "tolua_toboolean");
		if (lua_toboolean_p == nullptr)
			lua_toboolean_p = (lua_toboolean_t)app::LuaDLL_tolua_toboolean;
		lua_type_p = (lua_type_t)GetProcAddress(xlua, "lua_type");
		if (lua_type_p == nullptr)
			lua_type_p = (lua_type_t)app::LuaDLL_lua_type;
		lua_tolstring_p = (lua_tolstring_t)GetProcAddress(xlua, "lua_tolstring");
		if (lua_tolstring_p == nullptr)
			lua_tolstring_p = (lua_tolstring_t)app::LuaDLL_lua_tolstring;

		if (m_State == nullptr)
			m_State = luaL_newstate();

		if (m_State != NULL)
			luaL_openlibs(m_State);
		else
			LOG_ERROR("Failed to create Lua state");

		if (!f_Code.value().empty())
			m_Editor.SetText(f_Code.value());

		//events::GameUpdateEvent += MY_METHOD_HANDLER(LuaEditor::OnGameUpdate);
	}

	void LuaEditor::DrawExternal()
	{
		ImGui::Begin("Lua Editor", nullptr, ImGuiWindowFlags_MenuBar);
		
		ImGui::SetWindowSize(ImVec2(300.0f * 1.6f, 300.0f), ImGuiCond_FirstUseEver);

		auto langDef = TextEditor::LanguageDefinition::Lua();
		langDef.mAutoIndentation = true;

		m_Editor.SetLanguageDefinition(langDef);

		auto cpos = m_Editor.GetCursorPosition();

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save & Compile", "Ctrl-S", nullptr, m_TextChanged))
				{
					ApplyEditorChanges();
				}

				if (ImGui::MenuItem("Quit", "Esc"))
				{
					// Do nothing for now. Use Insert to hide this window.
					// CloseEditor();
				}

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("Edit"))
			{
				bool ro = m_Editor.IsReadOnly();
				if (ImGui::MenuItem("Read-only mode", nullptr, &ro))
					m_Editor.SetReadOnly(ro);

				ImGui::Separator();

				if (ImGui::MenuItem("Undo", "ALT-Backspace", nullptr, !ro && m_Editor.CanUndo()))
					m_Editor.Undo();
				if (ImGui::MenuItem("Redo", "Ctrl-Y", nullptr, !ro && m_Editor.CanRedo()))
					m_Editor.Redo();

				ImGui::Separator();

				if (ImGui::MenuItem("Copy", "Ctrl-C", nullptr, m_Editor.HasSelection()))
					m_Editor.Copy();
				if (ImGui::MenuItem("Cut", "Ctrl-X", nullptr, !ro && m_Editor.HasSelection()))
					m_Editor.Cut();
				if (ImGui::MenuItem("Delete", "Del", nullptr, !ro && m_Editor.HasSelection()))
					m_Editor.Delete();
				if (ImGui::MenuItem("Paste", "Ctrl-V", nullptr, !ro && ImGui::GetClipboardText() != nullptr))
					m_Editor.Paste();

				ImGui::Separator();

				if (ImGui::MenuItem("Select all", nullptr, nullptr))
					m_Editor.SetSelection(TextEditor::Coordinates(), TextEditor::Coordinates(m_Editor.GetTotalLines(), 0));

				ImGui::EndMenu();
			}

			if (ImGui::BeginMenu("View"))
			{
				if (ImGui::MenuItem("Dark palette"))
					m_Editor.SetPalette(TextEditor::GetDarkPalette());
				if (ImGui::MenuItem("Light palette"))
					m_Editor.SetPalette(TextEditor::GetLightPalette());
				if (ImGui::MenuItem("Retro blue palette"))
					m_Editor.SetPalette(TextEditor::GetRetroBluePalette());
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}

#define TEXT_WITH_DESC(desc, text, ...) { ImGui::Text(text, __VA_ARGS__); if (ImGui::IsItemHovered()) ImGui::SetTooltip(desc); }
#define SEPARATOR() ImGui::SameLine(0.0f, 0.0f); ImGui::Text(" | "); ImGui::SameLine(0.0f, 0.0f);

		TEXT_WITH_DESC("Line count", "%6d/%-6d %6d lines", cpos.mLine + 1, cpos.mColumn + 1, m_Editor.GetTotalLines());
		SEPARATOR();
		TEXT_WITH_DESC("Is Overwrite", "%s", m_Editor.IsOverwrite() ? "Ovr" : "Ins");
		SEPARATOR();
		TEXT_WITH_DESC("Can undo", "%s", m_Editor.CanUndo() ? "*" : " ");
		//if (m_Script->GetType() == script::ScriptType::FileScript)
		//{
		//    auto filescript = reinterpret_cast<script::FileScript*>(m_Script);

		//    SEPARATOR();
		//    TEXT_WITH_DESC("Filename", "%s", filescript->GetFilePath().c_str());
		//}

#undef TEXT_WITH_DESC
#undef SEPARATOR

		ImGui::PushStyleColor(ImGuiCol_ScrollbarBg, ImVec4(0, 0, 0, 0));
		{
			m_Editor.Render("TextEditor");
			auto ctx = ImGui::GetCurrentContext();
			// InputLocker::SetLock(this, ctx->IO.WantCaptureKeyboard);
		}
		ImGui::PopStyleColor();

		m_TextChanged |= m_Editor.IsTextChanged();

		ImGui::End();

		static Hotkey saveHotkey = Hotkey({ VK_LCONTROL, 'S' });

		if (saveHotkey.IsReleased())
			ApplyEditorChanges();
	}

	void LuaEditor::Compile(const std::string& code)
	{
		if (m_State == nullptr)
		{
			LOG_ERROR("Lua state is null");
			return;
		}

		if (luaL_loadbufferx_p(m_State, code.c_str(), code.size(), "LuaScript", NULL) != LUA_OK)
		{
			const char* error_msg = lua_tolstring_p(m_State, -1, NULL);
			LOG_ERROR("Error compiling Lua script: %s", error_msg);
			lua_pop(m_State, 1);
			return;
		}

		if (lua_pcall_p(m_State, 0, LUA_MULTRET, 0) != LUA_OK)
		{
			const char* error_msg = lua_tolstring_p(m_State, -1, NULL);
			LOG_ERROR("Error executing Lua script: %s", error_msg);
			lua_pop(m_State, 1);
			return;
		}

		LOG_DEBUG("Lua script executed successfully");
	}

	void LuaEditor::ApplyEditorChanges()
	{
		auto textToSave = m_Editor.GetText();
		f_Code.value() = textToSave;
		Compile(textToSave);
	}

	void LuaEditor::OpenEditor()
	{
		m_Enabled = true;
	}

	void LuaEditor::CloseEditor()
	{
		m_Enabled = false;
	}

	void LuaEditor::ToggleEditor()
	{
		m_Enabled = !m_Enabled;
		if (m_Enabled)
			OpenEditor();
		else
			CloseEditor();
	}

	void LuaEditor::OnGameUpdate()
	{
	}
}
