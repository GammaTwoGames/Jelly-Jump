#ifndef WALLS_H_INCLUDED
#define WALLS_H_INCLUDED

using namespace std;
using namespace sf;

#include "triangle3d.h"
#include "rectangle.h"
#include "pol_arr.h"
#include "ball.h"

class Walls : public Pol_struct
{
private:
    int z_gen;
public:
    Walls(int jj)
    {
        for (int i = - 1; i < 3; i ++)
            push_walls_of_level(&polygons, i);
        z_gen = 3;
    }
    void app(float *zi)
    {
        if (z_gen*5 - z < 10) {push_walls_of_level(&polygons, z_gen); z_gen++;}
    }

};

class Sea : public Pol_struct
{
public:
    Sea(int jj)
    {
        polygons.clear();
    }
    void app(float *zi)
    {
        polygons.clear();
         for (int i = - 4; i < 4; i ++)
            for (int j = 1; j < 15; j ++)
            {
                int c = j*18;
                polygons.push_back(Triangle3D(Point3D(i,sea_level,j,Color(c*0.9,c*0.9,c)),
                                            Point3D(i + 1,sea_level,j,Color(c*0.9,c*0.9,c)),
                                            Point3D(i,sea_level,j + 1,Color(c*0.9,c*0.9,c))
                                            ));
                polygons.push_back(Triangle3D(Point3D(i+1,sea_level,j+1,Color(c*0.9,c*0.9,c)),
                                            Point3D(i + 1,sea_level,j,Color(c*0.9,c*0.9,c)),
                                            Point3D(i,sea_level,j + 1,Color(c*0.9,c*0.9,c))
                                            ));
            }
    }

};

class Jelly : public Pol_struct
{
private:
    Ball ball;
public:
    Jelly(int jj)
    {

    }
    void app(float time)
    {
        ball.app(time);
        polygons.clear();
        push_rect_orange(&polygons, -0.5, ball.zb, 4, 1, 1, 0.5, 0);
    }
    void jump()
    {
        ball.jump();
    }

    float get_speed()
    {
        return ball.uz;
    }
    float get_z()
    {
        return ball.zb;
    }

};

#endif // WALLS_H_INCLUDED
