#include <cmath>
#include <cstdlib>
#include <ctime>
#include <random>


#include "Math.h"


Vector::Vector() {
	reset();
}


Vector::Vector(float x, float y) {
	set(x, y);
}


Vector::Vector(const Vector & v) {
	set(v.mX, v.mY);
}


Vector::~Vector() {

}


int Vector::x() {
	return int(mX);
}


int Vector::y() {
	return int(mY);
}


float Vector::xf() {
	return mX;
}


float Vector::yf() {
	return mY;
}


void Vector::reset() {
	set(0.0f, 0.0f);
}


void Vector::set(float x, float y) {
	this->mX = x;
	this->mY = y;
}


void Vector::setX(float x) {
	set(x, this->mY);
}


void Vector::setY(float y) {
	set(this->mX, y);
}


void Vector::add(float x, float y) {
	set(mX + x, mY + y);
}


void Vector::addX(float x) {
	set(mX + x, mY);
}


void Vector::addY(float y) {
	set(mX, mY + y);
}


bool Vector::isZero() {
	return (mX == 0.0f && mY == 0.0f);
}


float Vector::length() {
	return std::sqrtf(mX*mX + mY*mY);
}

Vector Vector::normalized() {
	return (*this) / length();
}

Vector Vector::reciprocal() {
	Vector v;
	v.set(-this->mY, this->mX);
	return v;
}

Vector Vector::operator+(Vector v) {
	Vector res;
	res.set(this->mX + v.mX, this->mY + v.mY);
	return res;
}


Vector Vector::operator-(Vector v) {
	Vector res;
	res.set(this->mX - v.mX, this->mY - v.mY);
	return res;
}


Vector Vector::operator*(int s) {
	Vector res;
	res.set(this->mX * s, this->mY * s);
	return res;
}


Vector Vector::operator*(float s) {
	Vector res;
	res.set(this->mX * s, this->mY * s);
	return res;
}


Vector Vector::operator/(int s) {
	Vector res;
	res.set(this->mX / s, this->mY / s);
	return res;
}


Vector Vector::operator/(float s) {
	Vector res;
	res.set(this->mX / s, this->mY / s);
	return res;
}


Vector Vector::scale(Vector v) {
	Vector res;
	res.set(this->mX * v.mX, this->mY * v.mY);
	return res;
}


Vector & Vector::operator=(const Vector & v) {
	set(v.mX, v.mY);
	return *this;
}


Rectangle::Rectangle() {
	reset();
}


Rectangle::Rectangle(int x1, int y1, int x2, int y2) {
	if (x2 > x1) {
		int temp = x2;
		x2 = x1;
		x1 = temp;
	}
	if (y2 > y1) {
		
	}
	set(x1, y1, x2, y2);
}


Rectangle::Rectangle(Rectangle & r) {
	set(r.mX1, r.mY2, r.mX2, r.mY2);
}


Rectangle::~Rectangle() {

}


int Rectangle::x1() {
	return mX1;
}


int Rectangle::y1() {
	return mY1;
}


int Rectangle::x2() {
	return mX2;
}


int Rectangle::y2() {
	return mY2;
}


void Rectangle::reset() {
	set(0, 0, 0, 0);
}

// TODO add a condition that always ensures x2 is to the right of x1
// and that y2 is above y1
// also TODO make game coords have Y as up?
void Rectangle::set(int x1, int y1, int x2, int y2) {
	mX1 = x1;
	mY1 = y1;
	mX2 = x2;
	mY2 = y2;
}


bool Rectangle::isZero() {
	return mX1 == 0 && mY1 == 0 && mX2 == 0 && mY2 == 0;
}


int Rectangle::width() {
	return std::abs(mX2 - mX1); // TODO may not need abs if I ensure x2 is always > x1
}


int Rectangle::height() {
	return std::abs(mY2 - mY1);
}


int Rectangle::size() {
	return height() * width();
}


bool Rectangle::intersects(Rectangle & r) {
	bool xcontains = (mX1 <= r.x1() && r.x1() <= mX2) || (mX1 <= r.x2() && r.x2() <= mX2);
	bool ycontains = (mY1 <= r.y1() && r.y1() <= mY2) || (mY1 <= r.y2() && r.y2() <= mY2);
	return xcontains && ycontains;
}


Vector Rectangle::intersectsAt(Rectangle & rect) {
	// TODO write this stuff
	Vector v;
	return v;
}


Vector Rectangle::center() {
	// TODO find out if this works while i figure out if i should make +Y up or down
	Vector v((mX2 - mX1)/2.0f, (mY2 - mY1)/2.0f);
	return v;
}


float randomNum() {
	static std::mt19937 generator((unsigned int) time(NULL));
	return (float) generator() / (float) generator.max();
}


float randomNum(float lower, float upper) {
	return lower + randomNum() * (upper - lower);
}


float moveTo(float value, float desired, float step) {
	if (value > desired)
		value = (value - step > desired) ? value - step : desired;
	else if (value < desired) {
		value = (value + step < desired) ? value + step : desired;
	}
	return value;
}


float clamp(float value, float first, float second) {
	if (first < second) {
		if (value < first)
			value = first;
		else if (second < value)
			value = second;
	}
	else if (second < first) {
		if (value < second)
			value = second;
		else if (first < value)
			value = first;
	}
	else {
		value = first;
	}
	return value;
}


bool withinEpsilon(float v1, float v2, float epsilon) {
	return (std::abs(v1) <= std::abs(v2) && std::abs(v1) + epsilon >= std::abs(v2)) ||
		   (std::abs(v2) <= std::abs(v1) && std::abs(v2) + epsilon >= std::abs(v1));
}