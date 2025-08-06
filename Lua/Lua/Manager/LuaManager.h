#pragma once

#include "Math/MyMath.h"

#include "../Script/LuaScript.h"
#include<unordered_map>

/* Luaスクリプトの管理を一元化するクラス */
class LuaManager {

private:

	// コンストラク、デストラクタ
	LuaManager() = default;
	~LuaManager() = default;
	LuaManager(const LuaManager&) = delete;
	const LuaManager& operator=(const LuaManager&) = delete;


public:

	/// <summary>
	/// インスタンス取得
	/// </summary>
	static LuaManager* GetInstance() {
		static LuaManager instance;
		return &instance;
	}

	/// <summary>
	/// 指定したLuaスクリプトの読み込み
	/// </summary>
	void LoadScript(const std::string& rootPath, const std::string& fileName);

	/// <summary>
	/// スクリプトのリロード
	/// </summary>
	void ReLoadScript(const std::string& scriptName);

	/// <summary>
	/// 指定したスクリプトを取得
	/// </summary>
	std::weak_ptr<LuaScript> GetScript(const std::string& scriptName);

	/// <summary>
	/// 指定したスクリプトを解放
	/// </summary>
	void UnLoadScript(const std::string& scriptName);

	/// <summary>
	/// スクリプトの変更を監視
	/// </summary>
	void MonitorScript();


private:

	// 管理中の LuaScript オブジェクト（キーはファイル名など任意の識別子）
	std::unordered_map<std::string, std::shared_ptr<LuaScript>> scripts_;
	// 各スクリプトのファイルパス
	std::unordered_map<std::string, std::filesystem::path> scriptPaths_;
	// 最終更新時刻の保持
	std::unordered_map<std::string, std::filesystem::file_time_type> scriptUpdateTimes_;

};
