#include "LuaManager.h"



/// <summary>
/// 指定したLuaスクリプトの読み込み
/// </summary>
void LuaManager::LoadScript(const std::string& rootPath, const std::string& fileName)
{
    std::filesystem::path fullPath = std::filesystem::path("Resources") / rootPath / fileName;
    std::string key = RemoveNameSuffix(fileName);

    if (!std::filesystem::exists(fullPath)) {
        std::cerr << "[Lua Error] Script file not found: " << fullPath << std::endl;
        return;
    }

    if (scripts_.find(key) != scripts_.end()) {
        std::cerr << "[Lua Warning] Script already loaded: " << key << std::endl;
        return;
    }

    auto script = std::make_shared<LuaScript>();
    if (!script->LoadScript(fullPath.string())) {
        std::cerr << "[Lua Error] Failed to load script: " << fullPath << std::endl;
        return;
    }

    scripts_[key] = script;
    scriptPaths_[key] = fullPath;
    // 初回ロード時の更新時刻も記録
    scriptUpdateTimes_[key] = std::filesystem::last_write_time(fullPath);
}


/// <summary>
/// スクリプトのリロード
/// </summary>
void LuaManager::ReLoadScript(const std::string& scriptName)
{
    auto it = scripts_.find(scriptName);
    if (it == scripts_.end()) {
        std::cerr << "[Lua Error] Script not found: " << scriptName << std::endl;
        return;
    }

    auto pathIt = scriptPaths_.find(scriptName);
    if (pathIt == scriptPaths_.end()) {
        std::cerr << "[Lua Error] Script path not found: " << scriptName << std::endl;
        return;
    }

    if (!it->second->Reload(pathIt->second.string())) {
        std::cerr << "[Lua Error] Failed to reload script: " << pathIt->second << std::endl;
        return;
    }

    std::cout << "[Lua Info] Reloaded script: " << scriptName << std::endl;
}


/// <summary>
/// 指定したスクリプトを取得
/// </summary>
std::weak_ptr<LuaScript> LuaManager::GetScript(const std::string& scriptName)
{
    try {
        return scripts_.at(scriptName);
    }
    catch (const std::out_of_range&) {
        return std::weak_ptr<LuaScript>();
    }
}


/// <summary>
/// 指定したスクリプトを解放
/// </summary>
void LuaManager::UnLoadScript(const std::string& scriptName)
{
    scripts_.erase(scriptName);
}


/// <summary>
/// スクリプトの変更を監視
/// </summary>
void LuaManager::MonitorScript()
{
    for (const auto& [scriptName, path] : scriptPaths_) {
        // 現在のファイル更新時刻を取得
        auto currentTime = std::filesystem::last_write_time(path);

        // 初回記録がなければ記録する（通常はLoadScript時に設定されるので不要なはず）
        if (scriptUpdateTimes_.find(scriptName) == scriptUpdateTimes_.end()) {
            scriptUpdateTimes_[scriptName] = currentTime;
            continue;
        }

        // 前回記録と異なっていればリロード
        if (scriptUpdateTimes_[scriptName] != currentTime) {
            std::cout << "Detected change in script: " << scriptName << std::endl;
            ReLoadScript(scriptName);
            // 更新後は時刻を更新
            scriptUpdateTimes_[scriptName] = currentTime;
        }
    }
}
