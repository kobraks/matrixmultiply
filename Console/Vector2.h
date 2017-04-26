#pragma once

#include "Typedeffs.h"

template <class T>
class Vector2
{
public:
	T x, y;

	Vector2(T _x, T _y) : x(_x), y(_y)
	{}

	Vector2() : x(T()), y(T())
	{}


#pragma region operators
	template<class Y, class = std::enable_if<std::is_arithmetic<Y>::value, Y>>
	Vector2<T>& operator=(const Vector2<Y>& _vector)
	{
		x = _vector.x;
		y = _vector.y;

		return *this;
	}

	bool operator == (const Vector2& _vector) const
	{
		return (_vector.x == x && _vector.y == y);
	}

	bool operator != (const Vector2& _vector) const
	{
		return !(*this == _vector);
	}

	template<class Y, class = std::enable_if<std::is_arithmetic<Y>::value, Y>>
	bool operator == (const Y& _number) const
	{
		return (x == _number && y == _number);
	}

	template<class Y, class = std::enable_if<std::is_arithmetic<Y>::value, Y>>
	bool operator != (const Y& _number) const
	{
		return !(*this == _number);
	}


	template<class Y, class = std::enable_if<std::is_arithmetic<Y>::value, Y>>
	Vector2<T>& operator += (const Y& _number)
	{
		x += _number;
		y += _number;

		return *this;
	}

	template<class Y, class = std::enable_if<std::is_arithmetic<Y>::value, Y>>
	Vector2<T>& operator -= (const Y& _number)
	{
		x -= _number;
		y -= _number;

		return *this;
	}

	Vector2<T>& operator ++ ()
	{
		++x;
		++y;

		return *this;
	}

	Vector2<T>& operator -- ()
	{
		--x;
		--y;

		return *this;
	}
#pragma endregion
};

typedef Vector2<char> Vector2c;
typedef Vector2<short> Vector2s;
typedef Vector2<int> Vector2i;
typedef Vector2<long> Vector2l;
typedef Vector2<long long> Vector2ll;

typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<long double> Vector2ld;

typedef Vector2<uchar> Vector2uc;
typedef Vector2<ushort> Vector2us;
typedef Vector2<ulong> Vector2ul;
typedef Vector2<uint> Vector2ui;
typedef Vector2<ullong> Vector2ull;