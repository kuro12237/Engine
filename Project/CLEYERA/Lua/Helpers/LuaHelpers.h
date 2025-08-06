#pragma once

#include "pch/Pch.h"


// --- ヘルパー関数：Luaスタックへ値をプッシュ ---
// int, float, double, std::string, const char* に対応
inline void PushValue(lua_State *L, int value) { lua_pushinteger(L, value); }

inline void PushValue(lua_State *L, float value) { lua_pushnumber(L, value); }

inline void PushValue(lua_State *L, double value) { lua_pushnumber(L, value); }

inline void PushValue(lua_State *L, const std::string &value) { lua_pushstring(L, value.c_str()); }

inline void PushValue(lua_State *L, const char *value) { lua_pushstring(L, value); }

inline void PushValue(lua_State *L, const Math::Vector::Vec2 &value) {
   lua_newtable(L); // 新しいテーブルを作成
   lua_pushnumber(L, value.x);
   lua_setfield(L, -2, "x");
   lua_pushnumber(L, value.y);
   lua_setfield(L, -2, "y");
}
inline void PushValue(lua_State *L, const Math::Vector::Vec3 &value) {
   lua_newtable(L); // 新しいテーブルを作成
   lua_pushnumber(L, value.x);
   lua_setfield(L, -2, "x");
   lua_pushnumber(L, value.y);
   lua_setfield(L, -2, "y");
   lua_pushnumber(L, value.z);
   lua_setfield(L, -2, "z");
}
inline void PushValue(lua_State *L, const Math::Vector::Vec4 &value) {
   lua_newtable(L); // 新しいテーブルを作成
   lua_pushnumber(L, value.x);
   lua_setfield(L, -2, "x");
   lua_pushnumber(L, value.y);
   lua_setfield(L, -2, "y");
   lua_pushnumber(L, value.z);
   lua_setfield(L, -2, "z");
   lua_pushnumber(L, value.w);
   lua_setfield(L, -2, "w");
}

// --- 可変引数を一括でプッシュするための再帰テンプレート関数 ---
// 最後の引数を処理する
template <typename T> void PushAll(lua_State *L, T value) {
   PushValue(L, value); // 引数が1つだけの場合、PushValueを呼び出す
}

// 引数が複数ある場合、再帰的にPushValueを呼び出す
template <typename T, typename... Args> void PushAll(lua_State *L, T value, Args... args) {
   PushValue(L, value); // 最初の引数を処理
   PushAll(L, args...); // 残りの引数を再帰的に処理
}