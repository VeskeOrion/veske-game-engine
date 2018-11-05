//----------------------------------------------------------------------------------------//
// Math.h
// Contains various classes that represent geometric primitives, like Vectors and
// Rectangles. The Entity class makes use of many of these primitives to keep track of
// position and collision (in development).
//----------------------------------------------------------------------------------------//


#ifndef MATH_H
#define MATH_H

enum Orientation { ORIENTATION_UP, ORIENTATION_DOWN, ORIENTATION_LEFT, ORIENTATION_RIGHT }; // up, down, left, right

class Vector {
private:
	float mX, mY;

public:
	Vector();
	Vector(float x, float y);
	Vector(Vector & v);
	~Vector();

	int x();
	int y();
	float xf();
	float yf();

	void reset();
	void set(float x, float y);
	void setX(float x);
	void setY(float y);
	void add(float x, float y);
	void addX(float x);
	void addY(float y);

	bool isZero();

	float length();
	Vector normalized();

	Vector operator+(Vector v);
	Vector operator-(Vector v);
	Vector operator*(int s);
	Vector operator*(float s);
	Vector operator/(int s);
	Vector operator/(float s);
	Vector scale(Vector v);
	Vector & operator=(Vector & v);
};


class Rectangle {
private:
	int mX1, mY1, mX2, mY2;

public:
	Rectangle();
	Rectangle(int x1, int y1, int x2, int y2);
	Rectangle(Rectangle & r);
	~Rectangle();

	int x1();
	int y1();
	int x2();
	int y2();

	void reset();
	void set(int x1, int y1, int x2, int y2);

	bool isZero();

	int width();
	int height();
	int size();

	bool intersects(Rectangle & rect);
	Vector intersectsAt(Rectangle & rect);
	Vector center();
};

float random();
float random(float lower, float upper);

float moveTo(float value, float desired, float step);
float clamp(float value, float first, float second);

bool withinEpsilon(float v1, float v2, float epsilon = 0.000001f);

#endif // MATH_H