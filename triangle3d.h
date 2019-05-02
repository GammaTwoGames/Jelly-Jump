#ifndef TRIANGLE3D_H_INCLUDED
#define TRIANGLE3D_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <cmath>
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
    float x1,y1,z1;
    Point3D()
    {

    }
    Point3D(float X, float Y, float Z)
    {
        x = X;
        y = Y;
        z = Z;
        x1 = x;
        y1 = y;
        z1 = z;
        c = Color(255,0,0);
    }
    Point3D(float X, float Y, float Z, Color C)
    {
        x = X;
        y = Y;
        z = Z;
        x1 = x;
        y1 = y;
        z1 = z;
        c = C;
    }
    Point2D project(float r, float yp)
    {
        //int sea_level = 3;
        //if ((y - yp) > -sea_level) {vis = 1;} else {vis = 0;}
        //Point2D ret(r*x/z, r*(((y - yp)>-sea_level)?(y - yp):(-sea_level))/z, c);
        if ((y ) > sea_level) {vis = 1;} else {vis = 0;}
        Point2D ret(r*x/z, r*((((y )>sea_level)?(y ):(sea_level)) - yp)/z, c);
        return ret;
    }
    void abel_transform(float x0, float y0, float z0, float k1, float angle)
    {
        x = x0 + k1*((x1 - x0)*cos(angle) - (y1 - y0)*sin(angle));
        y = y0 + k1*((y1 - y0)*cos(angle) + (x1 - x0)*sin(angle));
    }
    void change(float x0, float y0, float z0)
    {
        x1 += x0;
        y1 += y0;
        z += z0;
        abel_transform(x0, y0, z0, 1, 0);
    }
};

class Triangle3D
{
private:
    //Point3D p[3];
    //Point2D p_proj[3];
    float n;
public:
    Point3D p[3];
    Point2D p_proj[3];
    int vis;
    Triangle3D(Point3D P1, Point3D P2, Point3D P3)
    {
        p[0] = P1;
        p[1] = P2;
        p[2] = P3;
    }
    Triangle3D(Point3D P1, Point3D P2, Point3D P3, float N)
    {
        p[0] = P1;
        p[1] = P2;
        p[2] = P3;
        n = N;
    }
    void draw(RenderWindow* window, float yp)
    {
        for (int i = 0; i < 3; i ++) p_proj[i] = p[i].project(300, yp);
        ConvexShape polygon;
        polygon.setPointCount(3);
        Color outColor;
        //outColor = Color(p[0].c);
        polygon.setFillColor(p[0].c );
        for (int i = 0; i < 3; i ++) polygon.setPoint(i, Vector2f(432/2 + p_proj[i].x, 768 - 250 - 432/2 - p_proj[i].y));
        window->draw(polygon);
        vis = (int)p[0].vis + (int)p[1].vis + (int)p[2].vis;
    }
    float get_distance(float yp)
    {
        int xm = 1 ,ym = 1,zm = 2;
        return xm*(p[0].x + p[1].x + p[2].x)*(p[0].x + p[1].x + p[2].x) + ym*(p[0].y + p[1].y + p[2].y - 3*yp)*(p[0].y + p[1].y + p[2].y - 3*yp) + zm*(p[0].z + p[1].z + p[2].z)*(p[0].z + p[1].z + p[2].z);
    }
    void abel_transformation(float x0, float y0 ,float z0, float k1, float angle)
    {
        for (int i = 0; i < 3; i ++) p[i].abel_transform(x0,y0,z0,k1,angle);
    }
    void change(float x0, float y0 ,float z0)
    {
        for (int i = 0; i < 3; i ++) p[i].change(x0,y0,z0);
    }
    void culc_color(Color c)
    {
        float col = ((0.9 + 0.1*n));
        p[0].c = Color(c.r * col,c.g * col, c.b * col);
    }

};

class Triangle_transformable
{
public:
    float n[3], x[3][3];
    Triangle_transformable(float N[3], float X[3][3])
    {
        for (int k = 0; k < 3; k ++)
            for (int j = 0; j < 3; j ++)
                x[k][j] = X[k][j];
        for (int j = 0; j < 3; j ++)
            n[j] = N[j];
    }
    Triangle_transformable abel_transformation(float k, float angle)
    {
        Triangle_transformable ret(n, x);
        for (int k = 0; k < 3; k ++)
            for (int j = 0; j < 3; j ++)
                ret.x[k][j] *= k;
        for (int k = 0; k < 3; k ++)
        {
            ret.n[0] = ret.n[0]*cos(angle) - ret.n[1]*sin(angle);
            ret.n[1] = ret.n[1]*cos(angle) + ret.n[0]*sin(angle);
            ret.x[k][0] = ret.x[k][0]*cos(angle) - ret.x[k][1]*sin(angle);
            ret.x[k][1] = ret.x[k][1]*cos(angle) + ret.x[k][0]*sin(angle);
        }
    }
};



#endif // TRIANGLE3D_H_INCLUDED
