#pragma once
#include <DxLib.h>
#include <cmath>

	// 2Dベクトルクラス
	class Vector2 {
	public:
		// x成分,y成分
		double x, y;
		// コンストラクタ
		Vector2() noexcept = default;
		constexpr Vector2(double inX, double inY) noexcept
			: x{ inX }
			, y{ inY } {
		}
		// ベクトルの加算 a + b ※外部関数
		friend bool operator==(const Vector2& a, const Vector2& b) {
			if (a.x == b.x && a.y == b.y) {
				return true;
			}
			else {
				return false;
			}
		}
		// ベクトルの加算 a + b ※外部関数
		friend Vector2 operator+(const Vector2& a, const Vector2& b) {
			return { a.x + b.x, a.y + b.y };
		}
		// ベクトルの減算 a - b ※外部関数
		friend Vector2 operator-(const Vector2& a, const Vector2& b) {
			return { a.x - b.x, a.y - b.y };
		}
		// ベクトルのスカラー倍 v * scalar ※外部関数
		friend Vector2 operator*(const Vector2& v, double scalar) {
			return { v.x * scalar, v.y * scalar };
		}
		// ベクトルのスカラー倍 scalar * v ※外部関数
		friend Vector2 operator*(double scalar, const Vector2& v) {
			return { v.x * scalar, v.y * scalar };
		}

		// ベクトルのスカラー除算 scalar * v ※外部関数
		friend Vector2 operator/(const Vector2& v, double scalar) {
			return { v.x / scalar, v.y / scalar };
		}
		// ベクトル加算代入
		Vector2& operator+=(const Vector2& right) {
			x += right.x;
			y += right.y;
			return *this;
		}
		// ベクトル減算代入
		Vector2& operator-=(const Vector2& right) {
			x -= right.x;
			y -= right.y;
			return *this;
		}
		// ベクトルのスカラ乗算代入
		Vector2& operator*=(double scalar) {
			x *= scalar;
			y *= scalar;
			return *this;
		}
	};

	namespace Math {
		// 円周率
		constexpr float Pi = 3.1415926535f;
		constexpr float TwoPi = Pi * 2.0f;
		constexpr float PiOver2 = Pi / 2.0f;

		// 度数から孤度(ラジアン)に変換
		inline float ToRadians(float degrees) {
			return degrees * Pi / 180.0f;
		}
		// 孤度から度数(ディグリー)に変換
		inline float ToDegrees(float radians) {
			return radians * 180.0f / Pi;
		}
		// 二つの値の大きい値を取得
		template <typename T>
		T Max(const T& a, const T& b) {
			return (a < b ? b : a);
		}
		// 二つの値の小さい値を取得
		template <typename T>
		T Min(const T& a, const T& b) {
			return (a < b ? a : b);
		}
		// 二つの値の間でクランプする
		template <typename T>
		T Clamp(const T& value, const T& lower, const T& upper) {
			return Min(upper, Max(lower, value));
		}

	}
