#include "../include/GraphicsUtils.h"
#include "../include/Engine.h"

/**
 * Konstruktor klasy Point2D
 */
Point2D::Point2D(int _x, int _y)
{
  x = _x;
  y = _y;
}

Point2D::Point2D()
{
}

/**
 * Getter pola klasy Point2D
 * @return współrzędna na osi X
 */
int Point2D::getX()
{
  return x;
}

/**
 * Getter pola klasy Point2D
 * @return współrzędna na osi Y
 */
int Point2D::getY()
{
  return y;
}

/**
 * Setter pola x klasy Point2D
 */
void Point2D::setX(int value)
{
  x = value;
}

/**
 * Setter pola y klasy Point2D
 */
void Point2D::setY(int value)
{
  y = value;
}

/**
 * Setter pól x i y klasy Point2D
 */
void Point2D::setXY(int _x, int _y)
{
  x = _x;
  y = _y;
}

/**
 * Konstruktor klasy LineSegment
 */
LineSegment::LineSegment(Point2D A, Point2D B)
{
  pA = A;
  pB = B;
}

/**
 * Getter pola początku odcinka.
 * @return Point2D pA początek odcinka
 */
Point2D LineSegment::getPointA()
{
  return pA;
}

/**
 * Getter pola końca odcinka.
 * @return Point2D pB końca odcinka
 */
Point2D LineSegment::getPointB()
{
  return pB;
}

/**
 * Setter pola początku odcinka.
 */
void LineSegment::setPointA(int x, int y)
{
  pA.setX(x);
  pA.setY(y);
}

/**
 * Setter pola końca odcinka.
 */
void LineSegment::setPointB(int x, int y)
{
  pB.setX(x);
  pB.setY(y);
}

/**
 * Konstruktor klasy PrimitiveRenderer.
 */
PrimitiveRenderer::PrimitiveRenderer()
{
}

/**
 * Rysuje punkt w określonym kontekście
 */
void PrimitiveRenderer::drawPoint(Point2D point)
{
  SDL_RenderDrawPoint(
    renderer,
    point.getX(),
    point.getY()
  );
}

/**
 * Rysuje linie w określonym kontekście wykorzystując algorytm przyrostowy.
 */
void PrimitiveRenderer::drawLine(Point2D pointA, Point2D pointB)
{
  int x0 = pointA.getX();
  int y0 = pointA.getY();
  int x1 = pointB.getX();
  int y1 = pointB.getY();
  float dX = (float)(x1 - x0);
  float dY = (float)(y1 - y0);
  float steps;

  if (dX >= dY)
  {
    steps = dX;
  }
  else
  {
    steps = dY;
  }

  dX = dX/steps;
  dY = dY/steps;

  float x, y;
  x = x0;
  y = y0;

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  for (int i = 1; i <= steps; i++)
  {
    SDL_RenderDrawPoint(renderer, x, y);
    x += dX;
    y += dY;
  }
}

/**
 * Rysuje linie w określonym kontekście wykorzystując algorytm przyrostowy.
 */
void PrimitiveRenderer::drawLine(LineSegment line)
{
  int x0 = line.getPointA().getX();
  int y0 = line.getPointA().getY();
  int x1 = line.getPointB().getX();
  int y1 = line.getPointB().getY();
  float dX = (float)(x1 - x0);
  float dY = (float)(y1 - y0);
  float steps;

  if (dX >= dY)
  {
    steps = dX;
  }
  else
  {
    steps = dY;
  }

  dX = dX/steps;
  dY = dY/steps;

  float x, y;
  x = x0;
  y = y0;

  SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
  for (int i = 1; i <= steps; i++)
  {
    SDL_RenderDrawPoint(renderer, x, y);
    x += dX;
    y += dY;
  }
}

/**
 * Rysuje okrąg w określonym kontekście wykorzystując algorytm przyrostowy.
 */
void PrimitiveRenderer::drawCircle(int posX, int posY, int radius)
{
  int sred = radius * 2;
  int x = radius - 1;
  int y = 0;
  int tx = 1;
  int ty = 1;
  int err = tx - sred;

  while (x >= y)
  {
    drawPoint(Point2D(posX+x, posY-y));
    drawPoint(Point2D(posX+x, posY+y));
    drawPoint(Point2D(posX-x, posY-y));
    drawPoint(Point2D(posX-x, posY+y));

    drawPoint(Point2D(posX+y, posY-x));
    drawPoint(Point2D(posX+y, posY+x));
    drawPoint(Point2D(posX-y, posY-x));
    drawPoint(Point2D(posX-y, posY+x));

    if (err <= 0)
    {
      y++;
      err += ty;
      ty += 2;
    }

    if (err > 0)
    {
      x--;
      tx += 2;
      err += tx - sred;
    }

  }
}

/**
 * Rysuje prostokąt w określonym kontekście.
 */
void PrimitiveRenderer::drawRectangle(Point2D start, Point2D end, int r, int g, int b)
{
  int tmp;
  SDL_Rect rect;

  int x0, y0, x1, y1;
  x0 = start.getX();
  y0 = start.getY();
  x1 = end.getX();
  y1 = end.getY(); 

  if (x0 > x1)
  {
    tmp = x0;
    x0 = x1;
    x1 = tmp;
  }

  if (y0 > y1)
  {
    tmp = y0;
    y0 = y1;
    y1 = tmp;
  }

  rect.x = x0;
  rect.y = y0;
  rect.w = x1-x0;
  rect.h = y1-y0;

  SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
  SDL_RenderDrawRect(renderer, &rect);
}

/**
 * Rysuje wyznaczony przez dwie tablice x-ów i y-ów polygon.
 */
void PrimitiveRenderer::drawPolygon(int xs[], int ys[], int n)
{
  int nn;
  SDL_Point *points;

  if (n < 3)
  {
    return;
  }

  nn = n+1;
  points = (SDL_Point*)malloc(sizeof(SDL_Point)*nn);
  if (points == NULL)
  {
    return;
  }

  for (int i = 0; i < n; i++)
  {
    points[i].x = xs[i];
    points[i].y = ys[i];
  }

  points[n].x = xs[0];
  points[n].y = ys[0];

  SDL_RenderDrawLines(renderer, points, nn);
  free(points);
}