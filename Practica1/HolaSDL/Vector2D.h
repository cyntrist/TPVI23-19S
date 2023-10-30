#pragma once
#include <iostream>

template <class T = double>
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
	Vector2D operator+(const Vector2D& v) const {
		Vector2D r;
		r.x = this->x + v.x;
		r.y = this->y + v.y;
		return r;
	}
	Vector2D operator-(const Vector2D& v) const {
		Vector2D r;
		r.x = this->x - v.x;
		r.y = this->y - v.y;
		return r;
	}
	Vector2D operator*(double d) const {
		Vector2D r;
		r.x = x * d;
		r.y = y * d;
		return r;
	}
	Vector2D operator+=(const Vector2D& v) const {
		Vector2D r;
		r.x += v.x;
		r.y += v.y;
		return r;
	}
	T operator*(const Vector2D& d) const {
		return d.x * x + d.y * y;
	}
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v) {
		os << "(" << v.x << "," << v.y << ")";
		return os;
	}
};

template <class T = int>
using Point2D = Vector2D<T>;
