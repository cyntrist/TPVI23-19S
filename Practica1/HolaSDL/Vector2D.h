#pragma once
#include <iostream>

template <class T>
class Vector2D {
private:
	T x;
	T y;
public:
	Vector2D() {}
	Vector2D(T a, T b) {
		x = a;
		y = b;
	}
	double getX() const {
		return x;
	}
	double getY() const {
		return y;
	}
	Vector2D operator+(const Vector2D<T>& v) const {
		Vector2D r;
		r.x = this->x + v.x;
		r.y = this->y + v.y;
		return r;
	}
	Vector2D operator-(const Vector2D<T>& v) const {
		Vector2D<T> r;
		r.x = this->x - v.x;
		r.y = this->y - v.y;
		return r;
	}
	Vector2D operator*(double d) const {
		Vector2D<T> r;
		r.x = x * d;
		r.y = y * d;
		return r;
	}
	double operator*(const Vector2D<T>& d) const {
		return d.x * x + d.y * y;
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector2D<T>& v) {
		os << "(" << v.x << "," << v.y << ")";
		return os;
	}

	//using Point2D = Vector2D;
};

template <class T>
using Point2D = Vector2D<T>;
