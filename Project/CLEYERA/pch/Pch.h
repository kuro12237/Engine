#pragma once

#define VAR_NAME(var) (#var)
#define NOMINMAX

/// コンパイルファイル

#include <cassert>
#include <thread>
#include <algorithm>

#include <cstdint>
#include <format>
#include <wrl.h>

#include <chrono>
#include <numbers>
#include <random>

#include <array>
#include <list>
#include <map>
#include <queue>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <variant>
#include <vector>

#include <cstring>
#include <fstream>
#include <iomanip>
#include <span>
#include <sstream>
#include<filesystem>
#include <string>
#include <type_traits>

#include <iostream>
#include <comdef.h>
#include <Windows.h>
#pragma comment(lib, "winmm.lib")

#pragma region DirectX

#include <d3d12.h>
#include <d3d12shader.h>
#include <d3dcompiler.h>
#include <dxcapi.h>
#include <dxgi1_5.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>

#include"DirectXTex/DirectXTex.h"
#include"DirectXTex/d3dx12.h"

#pragma comment(lib, "d3dcompiler.lib")

#define DIRECTINPUT_VERSION 0x0800
#include <Xinput.h>
#include <dinput.h>
#pragma comment(lib, "xinput.lib")
#pragma comment(lib, "dinput8.lib")

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxcompiler.lib")

using namespace Microsoft::WRL;
#pragma endregion

#pragma region ImGui

#include <imgui.h>
#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

#pragma endregion

#pragma region Math

#include "math/MathInclude.h"
#pragma comment(lib, "math.lib")

#pragma endregion

#pragma region assimp

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#pragma endregion

#pragma region Json

#include <json.hpp>

#pragma endregion

#pragma region Lua

#include <lua.hpp>

#pragma endregion
