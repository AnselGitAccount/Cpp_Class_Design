#ifndef GUARD_SHAPE_H
#define GUARD_SHAPE_H


class Shape;
class Rectangle;
class Polygon;
class Circle;
class Ellipse;


class Shape {
public:
	virtual ~Shape() {};
};

class Rectangle : public Shape {};
class Polygon : public Shape {};
class Circle : public Shape {};
class Ellipse : public Shape {};


#endif
