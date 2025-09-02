#pragma once

#include "../Helpers/LuaHelpers.h"
#include "pch/Pch.h"

/* 個々のスクリプトを管理するクラス */
class LuaScript {

public:
  using ReloadCallback = std::function<void()>;

  /// <summary>
  /// コンストラクタ
  /// </summary>
  LuaScript();

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~LuaScript() = default;

  /// <summary>
  /// スクリプトの読み込み
  /// </summary>
  void LoadScript(const std::string &rootPath, const std::string &fileName);

  /// <summary>
  /// スクリプトの変更を監視
  /// </summary>
  void MonitorScript();

  /// <summary>
  /// スクリプトの再評価
  /// </summary>
  bool Reload(const std::string &file);

  /// <summary>
  /// リロード時のコールバックの登録
  /// </summary>
  void SetReloadCallBack(ReloadCallback callback);

  /// <summary>
  /// Lua側の変数を取得
  /// </summary>
  /// <typeparam name="T"> 取得変数の型 </typeparam>
  /// <param name="varName"> Lua側にある変数名 </param>
  template <typename T> T GetVariable(const std::string &varName);

  /// <summary>
  /// Lua側の関数を実行
  /// </summary>
  /// <param name="funcName"> Lua側にある関数名 </param>
  /// <param name="...args"> 引数 </param>
  template <typename... Args> bool ExeFunction(const std::string &funcName, Args... args);

  /// <summary>
  /// Lua側の関数を実行し、戻り値を受け取る
  /// </summary>
  template <typename Ret, typename... Args>
  std::optional<Ret> CallFunction(const std::string &funcName, Args... args);

private:
  /// <summary>
  /// スクリプトの読み込み＆エラーハンドリング処理
  /// </summary>
  bool LoadFromFile(const std::string &file);

private:
  // ステート
  std::unique_ptr<lua_State, decltype(&lua_close)> L_;

  // スクリプトのフルパス
  std::filesystem::path fullPath_;
  // 最終更新
  std::filesystem::file_time_type updateTime_;

  // コールバック関数
  ReloadCallback reloadCallback_ = nullptr;
};

/// <summary>
/// コンストラクタ
/// </summary>
inline LuaScript::LuaScript() : L_(luaL_newstate(), &lua_close) {
  luaL_openlibs(L_.get()); // Luaライブラリを開く
}

/// <summary>
/// スクリプトの読み込み
/// </summary>
inline void LuaScript::LoadScript(const std::string &rootPath, const std::string &fileName) {
  // フルパスを構築
  std::filesystem::path fullPath =
      std::filesystem::path("Resources/LuaScript") / rootPath / (fileName + ".lua");

  // ファイルが存在するか確認
  if (!std::filesystem::exists(fullPath)) {
    std::string errorMsg = "[Lua Error] Script file not found: " + fullPath.string();
    std::cerr << errorMsg << std::endl;
    throw std::runtime_error(errorMsg);
  }

  // Lua 用のパスに変換（区切り文字をスラッシュに統一）
  std::string luaPath = fullPath.string();
  std::replace(luaPath.begin(), luaPath.end(), '\\', '/');

  // 実際のLuaファイルの読み込み
  if (!LoadFromFile(luaPath)) {
    std::string errorMsg = "[Lua Error] Failed to load script: " + luaPath;
    std::cerr << errorMsg << std::endl;
    throw std::runtime_error(errorMsg);
  }

  // 読み込み成功時の情報保存
  fullPath_ = fullPath;
  updateTime_ = std::filesystem::last_write_time(fullPath);
}

/// <summary>
/// スクリプトの変更を監視
/// </summary>
inline void LuaScript::MonitorScript() {
  // 現在のファイル更新時刻を取得
  auto currentTime = std::filesystem::last_write_time(fullPath_);

  // 以前と異なっていれば変更とみなす
  if (updateTime_ != currentTime) {
    std::cout << "[Lua] Detected change in script: " << fullPath_ << std::endl;

    // スクリプト再読み込み（LoadScriptは更新済みのファイルパスを再利用）
    if (Reload(fullPath_.string())) {
      // 読み込み成功時のみ時刻を更新
      updateTime_ = currentTime;

      // コールバックがあれば呼び出す
      if (reloadCallback_) {
        reloadCallback_();
      }
    } else {
      std::cerr << "[Lua Error] Failed to reload script: " << fullPath_ << std::endl;
    }
  }
}

/// <summary>
/// スクリプトの再評価
/// </summary>
inline bool LuaScript::Reload([[maybe_unused]] const std::string &file) {
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
/// リロード時のコールバックの登録
/// </summary>
inline void LuaScript::SetReloadCallBack(ReloadCallback callback) { reloadCallback_ = callback; }

/// <summary>
/// スクリプトの読み込み＆エラーハンドリング処理
/// </summary>
inline bool LuaScript::LoadFromFile(const std::string &file) {
  if (luaL_dofile(L_.get(), file.c_str()) != LUA_OK) {
    std::cerr << "[Lua Error] Failed to load script: " << file << "\n"
              << lua_tostring(L_.get(), -1) << std::endl;
    lua_pop(L_.get(), 1); // スタックからエラーメッセージを削除
    return false;
  }
  return true;
}

/// <summary>
/// Lua側の変数を取得
/// </summary>
/// <typeparam name="T"> 取得変数の型 </typeparam>
/// <param name="varName"> Lua側にある変数名 </param>
template <typename T> inline T LuaScript::GetVariable(const std::string &varName) {
  std::istringstream ss(varName);
  std::string token;

  // 最初の変数名を取得
  std::getline(ss, token, '.');
  lua_getglobal(L_.get(), token.c_str()); // グローバル変数取得

  while (std::getline(ss, token, '.')) {
    if (!lua_istable(L_.get(), -1)) {
      lua_pop(L_.get(), 1);
      return T(); // 失敗時はデフォルト値を返す
    }

    lua_getfield(L_.get(), -1, token.c_str()); // 次のフィールドを取得
    lua_remove(L_.get(), -2);                  // 1つ前のテーブルを削除せずに保持する
  }

  // 型による処理を分ける
  if constexpr (std::is_same<T, int>::value || std::is_same<T, uint32_t>::value) {
    if (lua_isnumber(L_.get(), -1)) {
      int value = static_cast<int>(lua_tointeger(L_.get(), -1));
      lua_pop(L_.get(), 1);
      return value;
    }
  } else if constexpr (std::is_same<T, float>::value) {
    if (lua_isnumber(L_.get(), -1)) {
      float value = static_cast<float>(lua_tonumber(L_.get(), -1));
      lua_pop(L_.get(), 1);
      return value;
    }
  } else if constexpr (std::is_same<T, bool>::value) {
    if (lua_isboolean(L_.get(), -1)) {
      bool value = lua_toboolean(L_.get(), -1);
      lua_pop(L_.get(), 1);
      return value;
    }
  } else if constexpr (std::is_same<T, std::string>::value) {
    if (lua_isstring(L_.get(), -1)) {
      std::string value = lua_tostring(L_.get(), -1);
      lua_pop(L_.get(), 1);
      return value;
    }
  } else if constexpr (std::is_same<T, Math::Vector::Vec2>::value) {
    if (lua_istable(L_.get(), -1)) {
      Math::Vector::Vec2 vec;
      lua_getfield(L_.get(), -1, "x");
      vec.x = static_cast<float>(lua_tonumber(L_.get(), -1));
      lua_pop(L_.get(), 1);

      lua_getfield(L_.get(), -1, "y");
      vec.y = static_cast<float>(lua_tonumber(L_.get(), -1));
      lua_pop(L_.get(), 1);

      lua_pop(L_.get(), 1); // テーブル自体をポップ
      return vec;
    }
  } else if constexpr (std::is_same<T, Math::Vector::Vec3>::value) {
    if (lua_istable(L_.get(), -1)) {
      Math::Vector::Vec3 vec;
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
  } else if constexpr (std::is_same<T, Math::Vector::Vec4>::value) {
    if (lua_istable(L_.get(), -1)) {
      Math::Vector::Vec4 vec;
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

  lua_pop(L_.get(), 1); // 失敗した場合はスタックをポップ
  return T();           // デフォルト値を返す
}
// 明示的なインスタンス化
template int LuaScript::GetVariable<int>(const std::string &);
template float LuaScript::GetVariable<float>(const std::string &);
template bool LuaScript::GetVariable<bool>(const std::string &);
template std::string LuaScript::GetVariable<std::string>(const std::string &);
template Math::Vector::Vec2 LuaScript::GetVariable<Math::Vector::Vec2>(const std::string &);
template Math::Vector::Vec3 LuaScript::GetVariable<Math::Vector::Vec3>(const std::string &);
template Math::Vector::Vec4 LuaScript::GetVariable<Math::Vector::Vec4>(const std::string &);

/// <summary>
/// Lua側の関数を実行
/// </summary>
/// <param name="funcName"> Lua側にある関数名 </param>
/// <param name="...args"> 引数 </param>
template <typename... Args>
inline bool LuaScript::ExeFunction(const std::string &funcName, Args... args) {
  lua_State *L = L_.get();
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
    std::cerr << "[Lua Error] Error calling function " << funcName << ": " << lua_tostring(L, -1)
              << std::endl;
    lua_pop(L, 1);
    return false;
  }
  return true;
}

/// <summary>
/// Lua側の関数を実行し、戻り値を受け取る
/// </summary>
template <typename Ret, typename... Args>
inline std::optional<Ret> LuaScript::CallFunction(const std::string &funcName, Args... args) {
  lua_State *L = L_.get();
  lua_getglobal(L, funcName.c_str());

  if (!lua_isfunction(L, -1)) {
    std::cerr << "[Lua Error] Function not found: " << funcName << std::endl;
    lua_pop(L, 1);
    return std::nullopt;
  }

  PushAll(L, args...);

  if (lua_pcall(L, sizeof...(Args), 1, 0) != LUA_OK) {
    std::cerr << "[Lua Error] Error calling function " << funcName << ": " << lua_tostring(L, -1)
              << std::endl;
    lua_pop(L, 1);
    return std::nullopt;
  }

  Ret result{};
  if constexpr (std::is_same_v<Ret, int>) {
    result = static_cast<Ret>(lua_tointeger(L, -1));
  } else if constexpr (std::is_same_v<Ret, float>) {
    result = static_cast<Ret>(lua_tonumber(L, -1));
  } else if constexpr (std::is_same_v<Ret, double>) {
    result = static_cast<Ret>(lua_tonumber(L, -1));
  } else if constexpr (std::is_same_v<Ret, std::string>) {
    result = std::string(lua_tostring(L, -1));
  } else {
    std::cerr << "[Lua Error] Unsupported return type" << std::endl;
    lua_pop(L, 1);
    return std::nullopt;
  }

  lua_pop(L, 1);
  return result;
}
