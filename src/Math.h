#ifndef MATH_H
#define MATH_H

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
#endif // MATH_H