#pragma once

/**
 * @file Easing.h
 * @brief イージング関数のまとめ
 * @author 茂木翼
 */

//ここでのイージング関数はここから持ってきた
//https://easings.net/ja

#include <cmath>
#include <numbers>
#include <algorithm>

/// <summary>
/// イージング
/// </summary>
namespace Easing{
	
	/// <summary>
	/// 直線
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	inline float_t EaseStreat(const float_t& value) {
		//0.0fから1.0fに変換する
		return std::clamp(value, 0.0f, 1.0f);
	}

	#pragma region Sine
	/// <summary>
	/// SineのIn
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseInSine(const float_t& value) {
		//計算
		float_t result = 1.0f - std::cosf((value * std::numbers::pi_v<float_t>) / 2.0f);
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// SineのOut
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseOutSine(const float_t& value) {
		//計算
		float_t result = std::sinf((value * std::numbers::pi_v<float_t>) / 2.0f);
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// SineのInとOut
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseInOutSine(const float_t& value) {
		//計算
		float_t result = -(std::cosf(std::numbers::pi_v<float_t> *value) - 1.0f) / 2.0f;
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	#pragma endregion

	#pragma region Quad
	/// <summary>
	///　QuadのIn
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseInQuad(const float_t& value) {
		//計算
		float_t result = value * value;
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// QuadのOut
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseOutQuad(const float_t& value) {
		//計算
		float_t result = 1.0f - (1.0f - value) * (1.0f - value);
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// QuadのInとOut
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	inline float_t EaseInOutQuad(const float_t& value) {
		//計算
		float_t result = 0.0f;
		if (value < 0.5f) {
			result = 2.0f * value * value;
		}
		else {
			result = 1.0f - std::pow(-2.0f * value + 2.0f, 2.0f) / 2.0f;
		}

		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	}

	#pragma endregion

	#pragma region Cubic
	/// <summary>
	///　CubicのIn
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseInCubic(const float_t& value) {
		//計算
		float_t result = value * value*value;
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// CubicのOut
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseOutCubic(const float_t& value) {
		//計算
		float_t result = 1.0f - std::powf(1.0f - value, 3.0f);
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// CubicのInとOut
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	inline float_t EaseInOutCubic(const float_t& value) {
		//計算
		float_t result = 0.0f;
		if (value < 0.5f) {
			result = 4.0f * value * value * value;
		}
		else {
			result = 1.0f - std::powf(-2.0f * value + 2.0f, 3.0f) / 2.0f;
		}

		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	}
	#pragma endregion

	#pragma region Quart
	/// <summary>
	/// QuartのIn
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseInQuart(const float_t& value) {
		//計算
		float_t result = value * value * value * value;
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// QuartのOut
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseOutQuart(const float_t& value) {
		//計算
		float_t result = 1.0f - std::powf(1.0f - value, 4.0f);
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// QuartのInとOut
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	inline float_t EaseInOutQuart(const float_t& value) {
		//計算
		float_t result = 0.0f;
		if (value < 0.5f) {
			result = 8.0f * value * value * value * value;
		}
		else {
			result = 1.0f - std::powf(-2.0f * value + 2.0f, 4.0f) / 2.0f;
		}

		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	}
	#pragma endregion

	#pragma region Back
	/// <summary>
	/// BackのIn
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseInBack(const float_t& value) {
		//指定された定数1
		const float_t value1 = 1.70158f;
		//指定された定数2
		const float_t value2 = value1 + 1.0f;

		//計算
		float_t result = value2 * value * value * value - value1 * value * value;
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// BackのOut
	/// </summary>
	/// <param name="value">値(t)</param>
	/// <returns></returns>
	inline float_t EaseOutBack(const float_t& value) {
		//指定された定数1
		const float_t value1 = 1.70158f;
		//指定された定数2
		const float_t value2 = value1 + 1.0f;

		//計算
		float_t result = 1.0f + value2 * std::powf(value - 1.0f, 3.0f) + value1 * std::powf(value - 1.0f, 2.0f);
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	};

	/// <summary>
	/// BackのInとOut
	/// </summary>
	/// <param name="value"></param>
	/// <returns></returns>
	inline float_t EaseInOutBack(const float_t& value) {
		//指定された定数1
		const float_t value1 = 1.70158f;
		//指定された定数2
		const float_t value2 = value1 * 1.525f;

		//計算
		float_t result = 0.0f;
		if (value < 0.5f) {
			result = (std::powf(2.0f * value, 2.0f) * ((value2 + 1.0f) * 2.0f * value - value2)) / 2.0f;
		}
		else {
			result = (std::powf(2.0f * value - 2.0f, 2.0f) * ((value2 + 1.0f) * (value * 2.0f - 2.0f) + value2) + 2.0f) / 2.0f;
		}
		//0.0fから1.0fに変換する
		return std::clamp(result, 0.0f, 1.0f);
	}
	#pragma endregion

};
