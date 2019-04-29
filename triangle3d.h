#ifndef TRIANGLE3D_H_INCLUDED
#define TRIANGLE3D_H_INCLUDED

#include <SFML/Graphics.hpp>
using namespace sf;

class Point2D
{
public:
    Color c;
    float x,y;
    Point2D()
    {

    }
    Point2D(float X, float Y, Color C)
    {
        x = X;
        y = Y;
        c = C;
    }
};

class Point3D
{
public:
    int vis = 1;
    Color c;
    float x,y,z;
    Point3D()
    {

    }
    Point3D(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
        c = Color(255,0,0);
    }
    Point3D(float X, float Y, float Z, Color C)
    {
        x = X;
        y = Y;
        z = Z;
        c = C;
    }
    Point2D project(float r, float yp)
    {
        if ((y - yp) > -3) {vis = 1;} else {vis = 0;}
        Point2D ret(r*x/z, r*(((y - yp)>-3)?(y - yp):(-3))/z, c);
        return ret;
    }
};

class Triangle3D
{
private:
    Point3D p[3];
    Point2D p_proj[3];
public:
    int vis;
    Triangle3D(Point3D P1, Point3D P2, Point3D P3)
    {
        p[0] = P1;
        p[1] = P2;
        p[2] = P3;
    }
    void draw(RenderWindow* window, float yp)
    {
        for (int i = 0; i < 3; i ++) p_proj[i] = p[i].project(300, yp);
        ConvexShape polygon;
        polygon.setPointCount(3);
        polygon.setFillColor(p[0].c);
        for (int i = 0; i < 3; i ++) polygon.setPoint(i, Vector2f(432/2 + p_proj[i].x, 768 - 50 - 432/2 - p_proj[i].y));
        window->draw(polygon);
        vis = (int)p[0].vis + (int)p[1].vis + (int)p[2].vis;
    }
    float get_distance(float yp)
    {
        int xm = 1 ,ym = 1,zm = 2;
        return xm*(p[0].x + p[1].x + p[2].x)*(p[0].x + p[1].x + p[2].x) + ym*(p[0].y + p[1].y + p[2].y - 3*yp)*(p[0].y + p[1].y + p[2].y - 3*yp) + zm*(p[0].z + p[1].z + p[2].z)*(p[0].z + p[1].z + p[2].z);
    }
};



#endif // TRIANGLE3D_H_INCLUDED
