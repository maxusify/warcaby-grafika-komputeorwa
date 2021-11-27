#ifndef PRIMITIVERENDERER_H
#define PRIMITIVERENDERER_H

#include <SDL2/SDL.h>

/** class Point2D
 *  brief klasa reprezentująca punkt na płaszczyźnie 2D
 */ 
class Point2D
{
public:
  Point2D();
  Point2D(int, int);
  int getX();
  int getY();
  void setX(int);
  void setY(int);
  void setXY(int, int);
  void drawPoint();

private:
  int x;
  int y;
};

/** class LineSegment
 *  brief klasa reprezentująca odcinek na płaszczyźnie 2D
 */ 
class LineSegment
{
public:
  LineSegment(Point2D, Point2D);
  LineSegment(int, int, int, int);
  Point2D getPointA();
  Point2D getPointB();
  void setPointA(int, int);
  void setPointB(int, int);

private:
  Point2D pA;
  Point2D pB;
};

/** class PrimitiveRenderer
 *  brief służy do rysowania obiektów na płaszczyźnie 2D
 */ 
class PrimitiveRenderer
{
public:
  PrimitiveRenderer();
  void drawPoint(Point2D);
  void drawLine(Point2D, Point2D);
  void drawLine(LineSegment);
  void drawCircle(int, int, int);
  void drawRectangle(Point2D start, Point2D end, int r, int g, int b);
  void drawPolygon(int vx[], int vy[], int n);
};

#endif /* PRIMITIVERENDERER_H */