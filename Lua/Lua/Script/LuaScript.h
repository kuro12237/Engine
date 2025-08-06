#pragma once

#include <lua.hpp>
#include <memory>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include<functional>


#include "../Helpers/LuaHelpers.h"
#include"math/MathInclude.h"


/* 個々のスクリプトを管理するクラス */
class LuaScript {

public:

    using ReloadCallback = std::function<void()>;  // コールバック型定義

	/// <summary>
	/// コンストラク
	/// </summary>
	LuaScript();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~LuaScript() = default;

	/// <summary>
	/// スクリプトの読み込み
	/// </summary>
	bool LoadScript(const std::string& file);

    /// <summary>
    /// スクリプトの再評価
    /// </summary>
    bool Reload(const std::string& file);

    /// <summary>
    /// コールバックを登録
    /// </summary>
    void SetReloadCallback(ReloadCallback callback);

	/// <summary>
	/// Lua側の変数を取得
	/// </summary>
	template <typename T>
	T GetVariable(const std::string& varName);

    /// <summary>
    /// Lua側の関数を実行（可変引数版）
    /// </summary>
    template <typename... Args>
    bool ExeFunction(const std::string& funcName, Args... args);



private:

    std::unique_ptr<lua_State, decltype(&lua_close)> L_;
    ReloadCallback reloadCallback_ = nullptr;  // コールバック関数

};



/// <summary>
/// コンストラク
/// </summary>
inline LuaScript::LuaScript() : L_(luaL_newstate(), &lua_close)
{
	luaL_openlibs(L_.get());  // Luaライブラリを開く
}


/// <summary>
/// スクリプトの読み込み
/// </summary>
inline bool LuaScript::LoadScript(const std::string& file)
{
	if (luaL_dofile(L_.get(), file.c_str()) != LUA_OK) {
		std::cerr << "[Lua Error] Failed to load script: " << file << "\n"
			<< lua_tostring(L_.get(), -1) << std::endl;
		lua_pop(L_.get(), 1); // スタックからエラーメッセージを削除
		return false;
	}
	return true;
}


/// <summary>
/// スクリプトの再評価
/// </summary>
inline bool LuaScript::Reload(const std::string& file)
{
    if (luaL_dofile(L_.get(), file.c_str()) != LUA_OK) {
        std::cerr << "[Lua Error] " << lua_tostring(L_.get(), -1) << std::endl;
        lua_pop(L_.get(), 1); // エラーメッセージをスタックから削除
        return false;
    }

    // コールバックが設定されていれば実行
    if (reloadCallback_) {
        reloadCallback_();
    }

    return true;
}


/// <summary>
/// コールバックを登録
/// </summary>
inline void LuaScript::SetReloadCallback(ReloadCallback callback)
{
    reloadCallback_ = callback;
}


/// <summary>
/// Lua側の変数を取得
/// </summary>
template<typename T>
inline T LuaScript::GetVariable(const std::string& varName)
{
    std::istringstream ss(varName);
    std::string token;

    // 最初の変数名を取得
    std::getline(ss, token, '.');
    lua_getglobal(L_.get(), token.c_str()); // グローバル変数取得

    while (std::getline(ss, token, '.')) {
        if (!lua_istable(L_.get(), -1)) {
            lua_pop(L_.get(), 1);
            return T();  // 失敗時はデフォルト値を返す
        }

        lua_getfield(L_.get(), -1, token.c_str());  // 次のフィールドを取得
        lua_remove(L_.get(), -2); // 1つ前のテーブルを削除せずに保持する
    }

    // 型による処理を分ける
    if constexpr (std::is_same<T, int>::value || std::is_same<T, uint32_t>::value) {
        if (lua_isnumber(L_.get(), -1)) {
            int value = static_cast<int>(lua_tointeger(L_.get(), -1));
            lua_pop(L_.get(), 1);
            return value;
        }
    }
    else if constexpr (std::is_same<T, float>::value) {
        if (lua_isnumber(L_.get(), -1)) {
            float value = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);
            return value;
        }
    }
    else if constexpr (std::is_same<T, bool>::value) {
        if (lua_isboolean(L_.get(), -1)) {
            bool value = lua_toboolean(L_.get(), -1);
            lua_pop(L_.get(), 1);
            return value;
        }
    }
    else if constexpr (std::is_same<T, std::string>::value) {
        if (lua_isstring(L_.get(), -1)) {
            std::string value = lua_tostring(L_.get(), -1);
            lua_pop(L_.get(), 1);
            return value;
        }
    }
    else if constexpr (std::is_same<T, Vector2>::value) {
        if (lua_istable(L_.get(), -1)) {
            Vector2 vec;
            lua_getfield(L_.get(), -1, "x");
            vec.x = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_getfield(L_.get(), -1, "y");
            vec.y = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_pop(L_.get(), 1); // テーブル自体をポップ
            return vec;
        }
    }
    else if constexpr (std::is_same<T, Vector3>::value) {
        if (lua_istable(L_.get(), -1)) {
            Vector3 vec;
            lua_getfield(L_.get(), -1, "x");
            vec.x = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_getfield(L_.get(), -1, "y");
            vec.y = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_getfield(L_.get(), -1, "z");
            vec.z = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_pop(L_.get(), 1); // テーブル自体をポップ
            return vec;
        }
    }
    else if constexpr (std::is_same<T, Vector4>::value) {
        if (lua_istable(L_.get(), -1)) {
            Vector4 vec;
            lua_getfield(L_.get(), -1, "x");
            vec.x = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_getfield(L_.get(), -1, "y");
            vec.y = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_getfield(L_.get(), -1, "z");
            vec.z = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_getfield(L_.get(), -1, "w");
            vec.w = static_cast<float>(lua_tonumber(L_.get(), -1));
            lua_pop(L_.get(), 1);

            lua_pop(L_.get(), 1); // テーブル自体をポップ
            return vec;
        }
    }

    lua_pop(L_.get(), 1);  // 失敗した場合はスタックをポップ
    return T();  // デフォルト値を返す
}
// 明示的なインスタンス化
template int LuaScript::GetVariable<int>(const std::string&);
template float LuaScript::GetVariable<float>(const std::string&);
template bool LuaScript::GetVariable<bool>(const std::string&);
template std::string LuaScript::GetVariable<std::string>(const std::string&);
template Vector2 LuaScript::GetVariable<Vector2>(const std::string&);
template Vector3 LuaScript::GetVariable<Vector3>(const std::string&);
template Vector4 LuaScript::GetVariable<Vector4>(const std::string&);


/// <summary>
/// Lua側の関数を実行
/// </summary>
template<typename ...Args>
inline bool LuaScript::ExeFunction(const std::string& funcName, Args ...args)
{
    lua_State* L = L_.get();
    // グローバル関数を取得
    lua_getglobal(L, funcName.c_str());
    if (!lua_isfunction(L, -1)) {
        std::cerr << "[Lua Error] Function not found: " << funcName << std::endl;
        lua_pop(L, 1);
        return false;
    }
    // 可変引数をスタックにプッシュ
    PushAll(L, args...);
    // 引数の数は sizeof...(Args)
    if (lua_pcall(L, sizeof...(Args), 0, 0) != LUA_OK) {
        std::cerr << "[Lua Error] Error calling function " << funcName << ": "
            << lua_tostring(L, -1) << std::endl;
        lua_pop(L, 1);
        return false;
    }
    return true;
}
